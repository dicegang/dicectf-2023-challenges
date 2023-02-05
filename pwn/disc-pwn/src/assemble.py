from dataclasses import dataclass
import random


class Instr(object):
    def __init__(self, parts, sp_adjust=0, pc_adjust=0, is_jump=False, break_multi=False, 
                 ser=lambda: b'', process=lambda *v: tuple(v)):
        self.parts = parts
        self.sp_adjust = sp_adjust
        self.pc_adjust = pc_adjust
        self.is_jump = is_jump
        self.break_multi = break_multi
        self.ser = ser
        self.process = process
        
    def render(self, pc, sp):
        lines = [
            x.format(
                sp=f'ctx->stack_idx + {sp}',
                pc=f'ctx->pc->i + {pc}'
            )
            for x in self.parts
        ]
        # return ['{', f'    ctx->debug({sp});'] + ['    ' + x for x in lines] + ['}']
        return ['{'] + ['    ' + x for x in lines] + ['}']

@dataclass
class Label(object):
    name: str
        
@dataclass
class TargetLabelPC(object):
    name: str
        
@dataclass
class TargetLabelMode(object):
    name: str
        
@dataclass
class TargetStringIdx(object):
    val: str
        
@dataclass
class TargetStringKey(object):
    val: str

def multi(ops, name='anon'):
    sp_adjust = 0
    pc_adjust = 0

    lines = []
    
    for op in ops:
        lines += op.render(pc_adjust, sp_adjust)
        sp_adjust += op.sp_adjust
        pc_adjust += op.pc_adjust
    
    if sp_adjust != 0:
        lines.append(f'ctx->stack_idx += {sp_adjust};')

    if pc_adjust != 0 and not ops[-1].is_jump:
        lines.append(f'ctx->pc->i += {pc_adjust};')

    return (
        f'void {name}(VMCtx *ctx) {{\n' + 
        '\n'.join('    ' + x for x in lines)
        + '\n}'
    )

def total_size(ops):
    return sum(x.pc_adjust for x in ops)

GET_INT = lambda name, off: f'obj_t {name} = make_shared<Int>(*(uint32_t *)(&rom[{{pc}} + {off}]));'
GET_U32 = lambda name, off: f'uint32_t {name} = *(uint32_t *)(&rom[{{pc}} + {off}]);'
GET_U8 = lambda name, off: f'uint8_t {name} = *(uint8_t *)(&rom[{{pc}} + {off}]);'
WRITE_STACK = lambda off, name: f'ctx->stack[{{sp}} + {off}] = {name};'
READ_STACK = lambda name, off: f'obj_t {name} = ctx->stack[{{sp}} + {off}];'

BINOP = lambda name, res, a, b: f'obj_t {res} = {a}->{name}({b});'
OPS = {
    'pushc': Instr([
        GET_INT('v', 0),
        WRITE_STACK(0, 'v')
    ], sp_adjust=1, pc_adjust=4, 
        ser=lambda x: int(x).to_bytes(4, 'little')),
    
    'pushs': Instr([
        GET_U32('sidx', 0),
        GET_U32('key', 4),
        # 'obj_t sval = defrob(sidx, key);',
        'obj_t sval = make_shared<String>(strtab[sidx]);',
        WRITE_STACK(0, 'sval')
    ], sp_adjust=1, pc_adjust=8,
        process=lambda *s: (TargetStringIdx(','.join(s)[1:-1]), TargetStringKey(','.join(s)[1:-1])),
        ser=lambda sidx, key: sidx.to_bytes(4, 'little') + key.to_bytes(4, 'little')),
    
    'add': Instr([
        READ_STACK('a', -1),
        READ_STACK('b', -2),
        BINOP('add', 'c', 'a', 'b'),
        WRITE_STACK(-2, 'c'),
    ], sp_adjust=-1, pc_adjust=0),

    'sub': Instr([
        READ_STACK('a', -1),
        READ_STACK('b', -2),
        BINOP('sub', 'c', 'a', 'b'),
        WRITE_STACK(-2, 'c'),
    ], sp_adjust=-1, pc_adjust=0),

    'mul': Instr([
        READ_STACK('a', -1),
        READ_STACK('b', -2),
        BINOP('mul', 'c', 'a', 'b'),
        WRITE_STACK(-2, 'c'),
    ], sp_adjust=-1, pc_adjust=0),
    
    'equals': Instr([
        READ_STACK('a', -1),
        READ_STACK('b', -2),
        BINOP('equals', 'c', 'a', 'b'),
        WRITE_STACK(-2, 'c'),
    ], sp_adjust=-1, pc_adjust=0),
    
    'lt': Instr([
        READ_STACK('a', -1),
        READ_STACK('b', -2),
        BINOP('lt', 'c', 'a', 'b'),
        WRITE_STACK(-2, 'c'),
    ], sp_adjust=-1, pc_adjust=0),

    'retv': Instr([
        'ctx->exit_flag = 1;',
        'ctx->exit_val = make_shared<Void>();'
    ], is_jump=True),
    
    'ret': Instr([
        READ_STACK('val', -1),
        'ctx->exit_flag = 1;',
        'ctx->exit_val = val->clone();'
    ], is_jump=True),
    
    'jump': Instr([
        GET_U32('tpc', 0),
        GET_U8('tmode', 4),
        'ctx->pc->i = tpc;',
        'ctx->mode = tmode;'
    ], pc_adjust=5, is_jump=True, 
        process=lambda name: (
            TargetLabelPC(name),
            TargetLabelMode(name)
        ),
        ser=lambda pc, mode: (
            int(pc).to_bytes(4, 'little') + 
            int(mode).to_bytes(1, 'little'))
        ),
    
    'jtrue': Instr([
        GET_U32('tpc', 0),
        GET_U8('tmode', 4),
        READ_STACK('val', -1),
        'if (dynamic_pointer_cast<Bool>(val)->b) {{ ctx->pc->i = tpc; ctx->mode = tmode; ctx->stack_idx = {sp} - 1; return; }}',
    ], pc_adjust=5, sp_adjust=-1, break_multi=True, 
        process=lambda name: (
            TargetLabelPC(name),
            TargetLabelMode(name)
        ),
        ser=lambda pc, mode: (
            int(pc).to_bytes(4, 'little') + 
            int(mode).to_bytes(1, 'little'))
        ),
    
    'jfalse': Instr([
        GET_U32('tpc', 0),
        GET_U8('tmode', 4),
        READ_STACK('val', -1),
        'if (!dynamic_pointer_cast<Bool>(val)->b) {{ ctx->pc->i = tpc; ctx->mode = tmode; ctx->stack_idx = {sp} - 1; return; }}',
    ], pc_adjust=5, sp_adjust=-1, break_multi=True, 
        process=lambda name: (
            TargetLabelPC(name),
            TargetLabelMode(name)
        ),
        ser=lambda pc, mode: (
            int(pc).to_bytes(4, 'little') + 
            int(mode).to_bytes(1, 'little'))
        ),
    
    'spawn': Instr([
        GET_U32('tpc', 0),
        GET_U8('tmode', 4),
        GET_U8('nargs', 5),
        'VMCtx inner(tpc, tmode);',
        'for (int i = 0; i < nargs; ++i) {{ inner.stack[inner.stack_idx++] = ctx->stack[{sp} - nargs + i]->clone(); }}',
        'obj_t res = inner.run();',
        'ctx->stack_idx -= nargs;',
        WRITE_STACK(0, 'res'),
    ], sp_adjust=1, pc_adjust=6, break_multi=True, # don't merge because this messes with sp
        process=lambda name, nargs: (
            TargetLabelPC(name),
            TargetLabelMode(name),
            int(nargs),
        ),
        ser=lambda pc, mode, nargs: (
            int(pc).to_bytes(4, 'little') + 
            int(mode).to_bytes(1, 'little') +
            int(nargs).to_bytes(1, 'little'))
        ),
    
    'mkarr': Instr([
        GET_U32('size', 0),
        'obj_t arr = make_shared<Array>(size);',
        WRITE_STACK(0, 'arr'),
    ], sp_adjust=1, pc_adjust=4,
        ser=lambda size: int(size).to_bytes(4, 'little')),
    
    'mkdict': Instr([
        'obj_t dict = make_shared<Dict>();',
        WRITE_STACK(0, 'dict')
    ], sp_adjust=1, pc_adjust=0),
    
    'setarr': Instr([
        READ_STACK('idx', -1),
        READ_STACK('val', -2),
        READ_STACK('arr', -3),
        'dynamic_pointer_cast<Array>(arr)->set(dynamic_pointer_cast<Int>(idx)->i, val);',
    ], sp_adjust=-2),
    
    'getarr': Instr([
        READ_STACK('idx', -1),
        READ_STACK('arr', -2),
        'obj_t val = dynamic_pointer_cast<Array>(arr)->get(dynamic_pointer_cast<Int>(idx)->i);',
        WRITE_STACK(-1, 'val')
    ]),
    
    'setdict': Instr([
        READ_STACK('key', -1),
        READ_STACK('val', -2),
        READ_STACK('dict', -3),
        'dynamic_pointer_cast<Dict>(dict)->set(dynamic_pointer_cast<String>(key)->s, val);',
    ], sp_adjust=-2),

    'getdict': Instr([
        READ_STACK('key', -1),
        READ_STACK('dict', -2),
        'obj_t val = dynamic_pointer_cast<Dict>(dict)->get(dynamic_pointer_cast<String>(key)->s);',
        WRITE_STACK(-2, 'val'),
    ], sp_adjust=-1),

    'hasdict': Instr([
        READ_STACK('key', -1),
        READ_STACK('dict', -2),
        'obj_t val = dynamic_pointer_cast<Dict>(dict)->has(dynamic_pointer_cast<String>(key)->s);',
        WRITE_STACK(-2, 'val'),
    ], sp_adjust=-1),
    
    'len': Instr([
        READ_STACK('item', -1),
        'obj_t val = make_shared<Int>(item->len());',
        WRITE_STACK(-1, 'val'),
    ], sp_adjust=0, pc_adjust=0),

    'value': Instr([
        READ_STACK('s', -1),
        'obj_t val = dynamic_pointer_cast<String>(s)->value();',
        WRITE_STACK(-1, 'val'),
    ], sp_adjust=0, pc_adjust=0),
    
    'substr': Instr([
        READ_STACK('size', -1),
        READ_STACK('start', -2),
        READ_STACK('val', -3),
        'obj_t sub = dynamic_pointer_cast<String>(val)->substr(start, size);',
        WRITE_STACK(-3, 'sub'),
    ], sp_adjust=-2, pc_adjust=0),
    
    'keys': Instr([
        READ_STACK('dict', -1),
        'obj_t arr = dynamic_pointer_cast<Dict>(dict)->keys();',
        WRITE_STACK(0, 'arr'),
    ], sp_adjust=1, pc_adjust=0),
    
    'swap': Instr([
        GET_U32('a', 0),
        GET_U32('b', 4),
        'obj_t x = ctx->stack[{sp} - a];',
        'obj_t y = ctx->stack[{sp} - b];',
        'ctx->stack[{sp} - b] = x;',
        'ctx->stack[{sp} - a] = y;',
    ], pc_adjust=8,
        ser=lambda a,b: int(a).to_bytes(4, 'little') + int(b).to_bytes(4, 'little')),
    
    'puts': Instr([
        READ_STACK('val', -1),
        'cout << dynamic_pointer_cast<String>(val)->s << endl;',
    ], sp_adjust=-1),
    
    'gets': Instr([
        'string line;',
        'getline(cin, line);',
        'obj_t val = make_shared<String>(line);',
        WRITE_STACK(0, 'val')
    ], sp_adjust=1),
    
    'dup': Instr([
        READ_STACK('val', -1),
        'obj_t other = val->clone();',
        WRITE_STACK(0, 'other')
    ], sp_adjust=1),
    
    'true': Instr([
        'obj_t val = make_shared<Bool>(true);',
        WRITE_STACK(0, 'val')
    ], sp_adjust=1),
    
    'false': Instr([
        'obj_t val = make_shared<Bool>(false);',
        WRITE_STACK(0, 'val')
    ], sp_adjust=1),

    'store': Instr([
        READ_STACK('addr', -1),
        READ_STACK('val', -2),
        'ctx->mem[dynamic_pointer_cast<Int>(addr)->i] = val;',
    ], sp_adjust=-2),

    'load': Instr([
        READ_STACK('addr', -1),
        'obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];',
        WRITE_STACK(-1, 'val'),
    ]),

    'debug': Instr([
        'ctx->print_info(0);',
    ], break_multi=True),

    'append': Instr([
        READ_STACK('val', -1),
        READ_STACK('arr', -2),
        'dynamic_pointer_cast<Array>(arr)->append(val);',
    ], sp_adjust=-1),

    'drop': Instr([
    ], sp_adjust=-1),

    'type': Instr([
        READ_STACK('val', -1),
        'obj_t res = make_shared<Int>(val->type());',
        WRITE_STACK(-1, 'res')
    ]),
}



def lift(code):
    lines = [x.strip() for x in code.strip().split('\n')]
    lines = [x for x in lines if x != '' and not x.startswith(';')]
    
    lifted = []
    for line in lines:
        if line.startswith('.'):
            lname = line[1:-1]
            lifted.append(Label(lname))
        else:
            parts = line.split(' ')
            
            opn = parts[0]
            args = ' '.join(parts[1:]).split(',')
            args = [x.strip() for x in args]
            if args == ['']:
                args = []
            
            # special case
            if opn == 'pushs':
                args = [' '.join(parts[1:])]
            
            op = OPS[opn]
            args = op.process(*args)
            
            lifted.append((op, opn, args))

    return lifted


def merge(lifted, max_merge=4, seed=0):
    random.seed(seed)
    
    out = []
    
    idx = 0
    while idx < len(lifted):
        pack = []
        args = []
        hit_label = None
        for j in range(random.randint(1,max_merge)):
            if idx >= len(lifted):
                break
            
            curr = lifted[idx]
            idx += 1
            
            if type(curr) is Label:
                hit_label = curr
                break
            else:
                op = curr[0]
                pack.append(op)
                args.append(curr[2])
                
                # break on jumps
                if op.is_jump or op.break_multi:
                    break
        
        if len(pack) > 0:
            out.append((tuple(pack), args))
        if hit_label is not None:
            out.append(hit_label)
    
    return out

def fixup(arg, label_map, string_table, string_map):
    match arg:
        case TargetLabelPC(name):
            return label_map[name]
        case TargetLabelMode(name):
            return 0
        case TargetStringIdx(val):
            return string_map[val]
        case TargetStringKey(val):
            return string_table[string_map[val]][1]
        case _:
            return arg

def merge_resolve(merged, seed=0):
    random.seed(seed)

    out = []
    
    # --- Find labels ---
    label_map = {}
    pc = 0
    for x in merged:
        if type(x) is Label:
            label_map[x.name] = pc
        else:
            ops = x[0]
            pc += 1 + total_size(ops)
    # --------
    print('labels: ', label_map)
    
    # --- Find strings ---
    string_table = []
    string_map = {}

    pc = 0
    for x in merged:
        if type(x) is Label:
            pass
        else:
            args = x[1]
            for op_args in args:
                for arg in op_args:
                    if type(arg) is TargetStringIdx:
                        sval = arg.val
                        if sval not in string_map:
                            string_table.append((sval, 0))
                            string_map[sval] = len(string_table) - 1
    # --------    
    print('strings: ', string_table)
    
    
    pc = 0
    for x in merged:
        if type(x) is Label:
            continue
        else:
            ops, args = x
            
            args = [
                [fixup(x, label_map, string_table, string_map) for x in p]
                for p in args
            ]
            
            print(args)
            
            rom = b''.join(
                o.ser(*a) for o,a in zip(ops, args)
            )
            
            out.append((ops, rom))
            
    return out, string_table

def gen_rom(merged):
    curr = 0
    op_map = {}
    
    rom = b''
    for pack, partial_rom in merged:
        if not pack in op_map:
            op_map[pack] = curr
            curr += 1
        
        cid = op_map[pack]
        
        rom += cid.to_bytes(1, 'little') + partial_rom
        
    return rom, op_map

def write_rom(rom):
    # out = 'uint8_t rom[] = {' + ','.join(str(x) for x in rom) + '};\n'
    # open('./rom.h', 'w').write(out)

    open('./rom.dat', 'wb').write(bytes(rom))

def write_functable(op_map):
    out = ''

    names = []
    for pack in op_map:
        name = f'func_{op_map[pack]}'
        names.append(name)
        res = multi(list(pack), name=name)
        out += res + '\n\n'
        
    out += 'vm_func_t functions[] = {' + ','.join(names) + '};\n'
    
    open('./ops.h', 'w').write(out)

def write_string_table(string_table):
    out = ''
    
    out += 'const char *strtab[] = {\n'
    out += '\n'.join('    "' + x + '",' for x,k in string_table)
    out += '\n};\n'
    
    open('./strtab.h', 'w').write(out)


if __name__=='__main__':
    code = open('./code.txt', 'r').read()

    lf = lift(code)
    m = merge(lf, seed=2)
    m, string_table = merge_resolve(m)
    rom, op_map = gen_rom(m)

    write_functable(op_map)
    write_rom(rom)
    write_string_table(string_table)

    print('done!')
