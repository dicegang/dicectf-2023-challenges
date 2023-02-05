void func_0(VMCtx *ctx) {
    {
        uint32_t sidx = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint32_t key = *(uint32_t *)(&rom[ctx->pc->i + 0 + 4]);
        obj_t sval = make_shared<String>(strtab[sidx]);
        ctx->stack[ctx->stack_idx + 0 + 0] = sval;
    }
    ctx->stack_idx += 1;
    ctx->pc->i += 8;
}

void func_1(VMCtx *ctx) {
    {
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -1];
        cout << dynamic_pointer_cast<String>(val)->s << endl;
    }
    ctx->stack_idx += -1;
}

void func_2(VMCtx *ctx) {
    {
        string line;
        getline(cin, line);
        obj_t val = make_shared<String>(line);
        ctx->stack[ctx->stack_idx + 0 + 0] = val;
    }
    {
        uint32_t tpc = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint8_t tmode = *(uint8_t *)(&rom[ctx->pc->i + 0 + 4]);
        uint8_t nargs = *(uint8_t *)(&rom[ctx->pc->i + 0 + 5]);
        VMCtx inner(tpc, tmode);
        for (int i = 0; i < nargs; ++i) { inner.stack[inner.stack_idx++] = ctx->stack[ctx->stack_idx + 1 - nargs + i]->clone(); }
        obj_t res = inner.run();
        ctx->stack_idx -= nargs;
        ctx->stack[ctx->stack_idx + 1 + 0] = res;
    }
    ctx->stack_idx += 2;
    ctx->pc->i += 6;
}

void func_3(VMCtx *ctx) {
    {
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t other = val->clone();
        ctx->stack[ctx->stack_idx + 0 + 0] = other;
    }
    {
        obj_t val = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t res = make_shared<Int>(val->type());
        ctx->stack[ctx->stack_idx + 1 + -1] = res;
    }
    ctx->stack_idx += 1;
}

void func_4(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t a = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 1 + -2];
        obj_t c = a->equals(b);
        ctx->stack[ctx->stack_idx + 1 + -2] = c;
    }
    {
        uint32_t tpc = *(uint32_t *)(&rom[ctx->pc->i + 4 + 0]);
        uint8_t tmode = *(uint8_t *)(&rom[ctx->pc->i + 4 + 4]);
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -1];
        if (dynamic_pointer_cast<Bool>(val)->b) { ctx->pc->i = tpc; ctx->mode = tmode; ctx->stack_idx = ctx->stack_idx + 0 - 1; return; }
    }
    ctx->stack_idx += -1;
    ctx->pc->i += 9;
}

void func_5(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t idx = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t arr = ctx->stack[ctx->stack_idx + 1 + -2];
        obj_t val = dynamic_pointer_cast<Array>(arr)->get(dynamic_pointer_cast<Int>(idx)->i);
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    {
        uint32_t a = *(uint32_t *)(&rom[ctx->pc->i + 4 + 0]);
        uint32_t b = *(uint32_t *)(&rom[ctx->pc->i + 4 + 4]);
        obj_t x = ctx->stack[ctx->stack_idx + 1 - a];
        obj_t y = ctx->stack[ctx->stack_idx + 1 - b];
        ctx->stack[ctx->stack_idx + 1 - b] = x;
        ctx->stack[ctx->stack_idx + 1 - a] = y;
    }
    ctx->stack_idx += 1;
    ctx->pc->i += 12;
}

void func_6(VMCtx *ctx) {
    {
    }
    {
        uint32_t tpc = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint8_t tmode = *(uint8_t *)(&rom[ctx->pc->i + 0 + 4]);
        uint8_t nargs = *(uint8_t *)(&rom[ctx->pc->i + 0 + 5]);
        VMCtx inner(tpc, tmode);
        for (int i = 0; i < nargs; ++i) { inner.stack[inner.stack_idx++] = ctx->stack[ctx->stack_idx + -1 - nargs + i]->clone(); }
        obj_t res = inner.run();
        ctx->stack_idx -= nargs;
        ctx->stack[ctx->stack_idx + -1 + 0] = res;
    }
    ctx->pc->i += 6;
}

void func_7(VMCtx *ctx) {
    {
        uint32_t tpc = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint8_t tmode = *(uint8_t *)(&rom[ctx->pc->i + 0 + 4]);
        uint8_t nargs = *(uint8_t *)(&rom[ctx->pc->i + 0 + 5]);
        VMCtx inner(tpc, tmode);
        for (int i = 0; i < nargs; ++i) { inner.stack[inner.stack_idx++] = ctx->stack[ctx->stack_idx + 0 - nargs + i]->clone(); }
        obj_t res = inner.run();
        ctx->stack_idx -= nargs;
        ctx->stack[ctx->stack_idx + 0 + 0] = res;
    }
    ctx->stack_idx += 1;
    ctx->pc->i += 6;
}

void func_8(VMCtx *ctx) {
    {
        uint32_t tpc = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint8_t tmode = *(uint8_t *)(&rom[ctx->pc->i + 0 + 4]);
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -1];
        if (!dynamic_pointer_cast<Bool>(val)->b) { ctx->pc->i = tpc; ctx->mode = tmode; ctx->stack_idx = ctx->stack_idx + 0 - 1; return; }
    }
    ctx->stack_idx += -1;
    ctx->pc->i += 5;
}

void func_9(VMCtx *ctx) {
    {
        uint32_t sidx = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint32_t key = *(uint32_t *)(&rom[ctx->pc->i + 0 + 4]);
        obj_t sval = make_shared<String>(strtab[sidx]);
        ctx->stack[ctx->stack_idx + 0 + 0] = sval;
    }
    {
        uint32_t tpc = *(uint32_t *)(&rom[ctx->pc->i + 8 + 0]);
        uint8_t tmode = *(uint8_t *)(&rom[ctx->pc->i + 8 + 4]);
        ctx->pc->i = tpc;
        ctx->mode = tmode;
    }
    ctx->stack_idx += 1;
}

void func_10(VMCtx *ctx) {
    {
        ctx->exit_flag = 1;
        ctx->exit_val = make_shared<Void>();
    }
}

void func_11(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 1 + -2];
        ctx->mem[dynamic_pointer_cast<Int>(addr)->i] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + -1 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -2];
        ctx->mem[dynamic_pointer_cast<Int>(addr)->i] = val;
    }
    ctx->stack_idx += -2;
    ctx->pc->i += 8;
}

void func_12(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    {
        obj_t val = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t res = make_shared<Int>(val->type());
        ctx->stack[ctx->stack_idx + 1 + -1] = res;
    }
    ctx->stack_idx += 1;
    ctx->pc->i += 4;
}

void func_13(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t a = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 1 + -2];
        obj_t c = a->equals(b);
        ctx->stack[ctx->stack_idx + 1 + -2] = c;
    }
    {
        uint32_t tpc = *(uint32_t *)(&rom[ctx->pc->i + 4 + 0]);
        uint8_t tmode = *(uint8_t *)(&rom[ctx->pc->i + 4 + 4]);
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -1];
        if (!dynamic_pointer_cast<Bool>(val)->b) { ctx->pc->i = tpc; ctx->mode = tmode; ctx->stack_idx = ctx->stack_idx + 0 - 1; return; }
    }
    ctx->stack_idx += -1;
    ctx->pc->i += 9;
}

void func_14(VMCtx *ctx) {
    {
        uint32_t sidx = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint32_t key = *(uint32_t *)(&rom[ctx->pc->i + 0 + 4]);
        obj_t sval = make_shared<String>(strtab[sidx]);
        ctx->stack[ctx->stack_idx + 0 + 0] = sval;
    }
    {
        obj_t val = ctx->stack[ctx->stack_idx + 1 + -1];
        cout << dynamic_pointer_cast<String>(val)->s << endl;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 8 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    ctx->stack_idx += 1;
    ctx->pc->i += 12;
}

void func_15(VMCtx *ctx) {
    {
        uint32_t sidx = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint32_t key = *(uint32_t *)(&rom[ctx->pc->i + 0 + 4]);
        obj_t sval = make_shared<String>(strtab[sidx]);
        ctx->stack[ctx->stack_idx + 0 + 0] = sval;
    }
    {
        obj_t key = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t dict = ctx->stack[ctx->stack_idx + 1 + -2];
        obj_t val = dynamic_pointer_cast<Dict>(dict)->has(dynamic_pointer_cast<String>(key)->s);
        ctx->stack[ctx->stack_idx + 1 + -2] = val;
    }
    ctx->pc->i += 8;
}

void func_16(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    ctx->stack_idx += 1;
    ctx->pc->i += 4;
}

void func_17(VMCtx *ctx) {
    {
        uint32_t sidx = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint32_t key = *(uint32_t *)(&rom[ctx->pc->i + 0 + 4]);
        obj_t sval = make_shared<String>(strtab[sidx]);
        ctx->stack[ctx->stack_idx + 0 + 0] = sval;
    }
    {
        obj_t key = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t dict = ctx->stack[ctx->stack_idx + 1 + -2];
        obj_t val = dynamic_pointer_cast<Dict>(dict)->get(dynamic_pointer_cast<String>(key)->s);
        ctx->stack[ctx->stack_idx + 1 + -2] = val;
    }
    ctx->pc->i += 8;
}

void func_18(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    ctx->stack_idx += 1;
    ctx->pc->i += 4;
}

void func_19(VMCtx *ctx) {
    {
        obj_t a = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t c = a->equals(b);
        ctx->stack[ctx->stack_idx + 0 + -2] = c;
    }
    {
        uint32_t tpc = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint8_t tmode = *(uint8_t *)(&rom[ctx->pc->i + 0 + 4]);
        obj_t val = ctx->stack[ctx->stack_idx + -1 + -1];
        if (!dynamic_pointer_cast<Bool>(val)->b) { ctx->pc->i = tpc; ctx->mode = tmode; ctx->stack_idx = ctx->stack_idx + -1 - 1; return; }
    }
    ctx->stack_idx += -2;
    ctx->pc->i += 5;
}

void func_20(VMCtx *ctx) {
    {
        uint32_t sidx = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint32_t key = *(uint32_t *)(&rom[ctx->pc->i + 0 + 4]);
        obj_t sval = make_shared<String>(strtab[sidx]);
        ctx->stack[ctx->stack_idx + 0 + 0] = sval;
    }
    {
        obj_t val = ctx->stack[ctx->stack_idx + 1 + -1];
        cout << dynamic_pointer_cast<String>(val)->s << endl;
    }
    ctx->pc->i += 8;
}

void func_21(VMCtx *ctx) {
    {
        uint32_t sidx = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint32_t key = *(uint32_t *)(&rom[ctx->pc->i + 0 + 4]);
        obj_t sval = make_shared<String>(strtab[sidx]);
        ctx->stack[ctx->stack_idx + 0 + 0] = sval;
    }
    {
        obj_t key = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t dict = ctx->stack[ctx->stack_idx + 1 + -2];
        obj_t val = dynamic_pointer_cast<Dict>(dict)->has(dynamic_pointer_cast<String>(key)->s);
        ctx->stack[ctx->stack_idx + 1 + -2] = val;
    }
    {
        uint32_t tpc = *(uint32_t *)(&rom[ctx->pc->i + 8 + 0]);
        uint8_t tmode = *(uint8_t *)(&rom[ctx->pc->i + 8 + 4]);
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -1];
        if (!dynamic_pointer_cast<Bool>(val)->b) { ctx->pc->i = tpc; ctx->mode = tmode; ctx->stack_idx = ctx->stack_idx + 0 - 1; return; }
    }
    ctx->stack_idx += -1;
    ctx->pc->i += 13;
}

void func_22(VMCtx *ctx) {
    {
        uint32_t sidx = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint32_t key = *(uint32_t *)(&rom[ctx->pc->i + 0 + 4]);
        obj_t sval = make_shared<String>(strtab[sidx]);
        ctx->stack[ctx->stack_idx + 0 + 0] = sval;
    }
    {
        obj_t key = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t dict = ctx->stack[ctx->stack_idx + 1 + -2];
        obj_t val = dynamic_pointer_cast<Dict>(dict)->get(dynamic_pointer_cast<String>(key)->s);
        ctx->stack[ctx->stack_idx + 1 + -2] = val;
    }
    {
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t other = val->clone();
        ctx->stack[ctx->stack_idx + 0 + 0] = other;
    }
    {
        obj_t val = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t res = make_shared<Int>(val->type());
        ctx->stack[ctx->stack_idx + 1 + -1] = res;
    }
    ctx->stack_idx += 1;
    ctx->pc->i += 8;
}

void func_23(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 1 + -2];
        ctx->mem[dynamic_pointer_cast<Int>(addr)->i] = val;
    }
    {
        uint32_t sidx = *(uint32_t *)(&rom[ctx->pc->i + 4 + 0]);
        uint32_t key = *(uint32_t *)(&rom[ctx->pc->i + 4 + 4]);
        obj_t sval = make_shared<String>(strtab[sidx]);
        ctx->stack[ctx->stack_idx + -1 + 0] = sval;
    }
    ctx->pc->i += 12;
}

void func_24(VMCtx *ctx) {
    {
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -1];
        cout << dynamic_pointer_cast<String>(val)->s << endl;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + -1 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 0 + -1] = val;
    }
    ctx->pc->i += 4;
}

void func_25(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    {
        uint32_t sidx = *(uint32_t *)(&rom[ctx->pc->i + 4 + 0]);
        uint32_t key = *(uint32_t *)(&rom[ctx->pc->i + 4 + 4]);
        obj_t sval = make_shared<String>(strtab[sidx]);
        ctx->stack[ctx->stack_idx + 1 + 0] = sval;
    }
    {
        obj_t key = ctx->stack[ctx->stack_idx + 2 + -1];
        obj_t dict = ctx->stack[ctx->stack_idx + 2 + -2];
        obj_t val = dynamic_pointer_cast<Dict>(dict)->has(dynamic_pointer_cast<String>(key)->s);
        ctx->stack[ctx->stack_idx + 2 + -2] = val;
    }
    ctx->stack_idx += 1;
    ctx->pc->i += 12;
}

void func_26(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    {
        uint32_t sidx = *(uint32_t *)(&rom[ctx->pc->i + 4 + 0]);
        uint32_t key = *(uint32_t *)(&rom[ctx->pc->i + 4 + 4]);
        obj_t sval = make_shared<String>(strtab[sidx]);
        ctx->stack[ctx->stack_idx + 1 + 0] = sval;
    }
    {
        obj_t key = ctx->stack[ctx->stack_idx + 2 + -1];
        obj_t dict = ctx->stack[ctx->stack_idx + 2 + -2];
        obj_t val = dynamic_pointer_cast<Dict>(dict)->get(dynamic_pointer_cast<String>(key)->s);
        ctx->stack[ctx->stack_idx + 2 + -2] = val;
    }
    ctx->stack_idx += 1;
    ctx->pc->i += 12;
}

void func_27(VMCtx *ctx) {
    {
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t other = val->clone();
        ctx->stack[ctx->stack_idx + 0 + 0] = other;
    }
    {
        obj_t val = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t res = make_shared<Int>(val->type());
        ctx->stack[ctx->stack_idx + 1 + -1] = res;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 1 + 0] = v;
    }
    {
        obj_t a = ctx->stack[ctx->stack_idx + 2 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 2 + -2];
        obj_t c = a->equals(b);
        ctx->stack[ctx->stack_idx + 2 + -2] = c;
    }
    ctx->stack_idx += 1;
    ctx->pc->i += 4;
}

void func_28(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 1 + -2];
        ctx->mem[dynamic_pointer_cast<Int>(addr)->i] = val;
    }
    {
        uint32_t sidx = *(uint32_t *)(&rom[ctx->pc->i + 4 + 0]);
        uint32_t key = *(uint32_t *)(&rom[ctx->pc->i + 4 + 4]);
        obj_t sval = make_shared<String>(strtab[sidx]);
        ctx->stack[ctx->stack_idx + -1 + 0] = sval;
    }
    {
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -1];
        cout << dynamic_pointer_cast<String>(val)->s << endl;
    }
    ctx->stack_idx += -1;
    ctx->pc->i += 12;
}

void func_29(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + 1 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 2 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 2 + -2];
        ctx->mem[dynamic_pointer_cast<Int>(addr)->i] = val;
    }
    ctx->pc->i += 8;
}

void func_30(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + 1 + 0] = v;
    }
    ctx->stack_idx += 2;
    ctx->pc->i += 8;
}

void func_31(VMCtx *ctx) {
    {
        obj_t a = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t c = a->lt(b);
        ctx->stack[ctx->stack_idx + 0 + -2] = c;
    }
    {
        uint32_t tpc = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint8_t tmode = *(uint8_t *)(&rom[ctx->pc->i + 0 + 4]);
        obj_t val = ctx->stack[ctx->stack_idx + -1 + -1];
        if (dynamic_pointer_cast<Bool>(val)->b) { ctx->pc->i = tpc; ctx->mode = tmode; ctx->stack_idx = ctx->stack_idx + -1 - 1; return; }
    }
    ctx->stack_idx += -2;
    ctx->pc->i += 5;
}

void func_32(VMCtx *ctx) {
    {
        obj_t val = make_shared<Bool>(false);
        ctx->stack[ctx->stack_idx + 0 + 0] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 1 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 2 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 2 + -1] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + 2 + 0] = v;
    }
    ctx->stack_idx += 3;
    ctx->pc->i += 8;
}

void func_33(VMCtx *ctx) {
    {
        obj_t a = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t c = a->add(b);
        ctx->stack[ctx->stack_idx + 0 + -2] = c;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + -1 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + -1 + -2];
        ctx->mem[dynamic_pointer_cast<Int>(addr)->i] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + -3 + 0] = v;
    }
    ctx->stack_idx += -2;
    ctx->pc->i += 4;
}

void func_34(VMCtx *ctx) {
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 0 + -1] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t a = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 1 + -2];
        obj_t c = a->add(b);
        ctx->stack[ctx->stack_idx + 1 + -2] = c;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    ctx->stack_idx += 1;
    ctx->pc->i += 8;
}

void func_35(VMCtx *ctx) {
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -2];
        ctx->mem[dynamic_pointer_cast<Int>(addr)->i] = val;
    }
    {
        uint32_t tpc = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint8_t tmode = *(uint8_t *)(&rom[ctx->pc->i + 0 + 4]);
        ctx->pc->i = tpc;
        ctx->mode = tmode;
    }
    ctx->stack_idx += -2;
}

void func_36(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    {
        obj_t dict = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t arr = dynamic_pointer_cast<Dict>(dict)->keys();
        ctx->stack[ctx->stack_idx + 1 + 0] = arr;
    }
    ctx->stack_idx += 2;
    ctx->pc->i += 4;
}

void func_37(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 1 + -2];
        ctx->mem[dynamic_pointer_cast<Int>(addr)->i] = val;
    }
    ctx->stack_idx += -1;
    ctx->pc->i += 4;
}

void func_38(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    {
        obj_t item = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = make_shared<Int>(item->len());
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    ctx->stack_idx += 1;
    ctx->pc->i += 4;
}

void func_39(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    {
        obj_t a = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 1 + -2];
        obj_t c = a->lt(b);
        ctx->stack[ctx->stack_idx + 1 + -2] = c;
    }
    ctx->pc->i += 4;
}

void func_40(VMCtx *ctx) {
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 0 + -1] = val;
    }
    {
        obj_t idx = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t arr = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t val = dynamic_pointer_cast<Array>(arr)->get(dynamic_pointer_cast<Int>(idx)->i);
        ctx->stack[ctx->stack_idx + 0 + -1] = val;
    }
}

void func_41(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 1 + -2];
        ctx->mem[dynamic_pointer_cast<Int>(addr)->i] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + -1 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 0 + -1] = val;
    }
    ctx->pc->i += 8;
}

void func_42(VMCtx *ctx) {
    {
        obj_t item = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = make_shared<Int>(item->len());
        ctx->stack[ctx->stack_idx + 0 + -1] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t a = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 1 + -2];
        obj_t c = a->equals(b);
        ctx->stack[ctx->stack_idx + 1 + -2] = c;
    }
    ctx->pc->i += 4;
}

void func_43(VMCtx *ctx) {
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 0 + -1] = val;
    }
}

void func_44(VMCtx *ctx) {
    {
        obj_t key = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t dict = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t val = dynamic_pointer_cast<Dict>(dict)->get(dynamic_pointer_cast<String>(key)->s);
        ctx->stack[ctx->stack_idx + 0 + -2] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + -1 + 0] = v;
    }
    ctx->pc->i += 4;
}

void func_45(VMCtx *ctx) {
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -2];
        ctx->mem[dynamic_pointer_cast<Int>(addr)->i] = val;
    }
    ctx->stack_idx += -2;
}

void func_46(VMCtx *ctx) {
    {
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t res = make_shared<Int>(val->type());
        ctx->stack[ctx->stack_idx + 0 + -1] = res;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t a = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 1 + -2];
        obj_t c = a->equals(b);
        ctx->stack[ctx->stack_idx + 1 + -2] = c;
    }
    ctx->pc->i += 4;
}

void func_47(VMCtx *ctx) {
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 0 + -1] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    ctx->stack_idx += 1;
    ctx->pc->i += 4;
}

void func_48(VMCtx *ctx) {
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 0 + -1] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    ctx->stack_idx += 1;
    ctx->pc->i += 4;
}

void func_49(VMCtx *ctx) {
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 0 + -1] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    {
        obj_t s = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = dynamic_pointer_cast<String>(s)->value();
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    ctx->stack_idx += 1;
    ctx->pc->i += 4;
}

void func_50(VMCtx *ctx) {
    {
        obj_t a = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t c = a->add(b);
        ctx->stack[ctx->stack_idx + 0 + -2] = c;
    }
    ctx->stack_idx += -1;
}

void func_51(VMCtx *ctx) {
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -2];
        ctx->mem[dynamic_pointer_cast<Int>(addr)->i] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + -2 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + -1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + -1 + -1] = val;
    }
    ctx->stack_idx += -1;
    ctx->pc->i += 4;
}

void func_52(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t a = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 1 + -2];
        obj_t c = a->add(b);
        ctx->stack[ctx->stack_idx + 1 + -2] = c;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    ctx->stack_idx += 1;
    ctx->pc->i += 8;
}

void func_53(VMCtx *ctx) {
    {
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t res = make_shared<Int>(val->type());
        ctx->stack[ctx->stack_idx + 0 + -1] = res;
    }
}

void func_54(VMCtx *ctx) {
    {
        obj_t a = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t c = a->add(b);
        ctx->stack[ctx->stack_idx + 0 + -2] = c;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + -1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + -1 + -1] = val;
    }
    ctx->stack_idx += -1;
}

void func_55(VMCtx *ctx) {
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 0 + -1] = val;
    }
    {
        obj_t a = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t c = a->equals(b);
        ctx->stack[ctx->stack_idx + 0 + -2] = c;
    }
    {
        uint32_t tpc = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint8_t tmode = *(uint8_t *)(&rom[ctx->pc->i + 0 + 4]);
        obj_t val = ctx->stack[ctx->stack_idx + -1 + -1];
        if (!dynamic_pointer_cast<Bool>(val)->b) { ctx->pc->i = tpc; ctx->mode = tmode; ctx->stack_idx = ctx->stack_idx + -1 - 1; return; }
    }
    ctx->stack_idx += -2;
    ctx->pc->i += 5;
}

void func_56(VMCtx *ctx) {
    {
        obj_t a = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t c = a->add(b);
        ctx->stack[ctx->stack_idx + 0 + -2] = c;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + -1 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -2];
        ctx->mem[dynamic_pointer_cast<Int>(addr)->i] = val;
    }
    {
        uint32_t tpc = *(uint32_t *)(&rom[ctx->pc->i + 4 + 0]);
        uint8_t tmode = *(uint8_t *)(&rom[ctx->pc->i + 4 + 4]);
        ctx->pc->i = tpc;
        ctx->mode = tmode;
    }
    ctx->stack_idx += -2;
}

void func_57(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    {
        obj_t item = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = make_shared<Int>(item->len());
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + 1 + 0] = v;
    }
    ctx->stack_idx += 2;
    ctx->pc->i += 8;
}

void func_58(VMCtx *ctx) {
    {
        obj_t val = make_shared<Bool>(true);
        ctx->stack[ctx->stack_idx + 0 + 0] = val;
    }
    {
        obj_t val = ctx->stack[ctx->stack_idx + 1 + -1];
        ctx->exit_flag = 1;
        ctx->exit_val = val->clone();
    }
    ctx->stack_idx += 1;
}

void func_59(VMCtx *ctx) {
    {
        uint32_t sidx = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint32_t key = *(uint32_t *)(&rom[ctx->pc->i + 0 + 4]);
        obj_t sval = make_shared<String>(strtab[sidx]);
        ctx->stack[ctx->stack_idx + 0 + 0] = sval;
    }
    {
        obj_t val = ctx->stack[ctx->stack_idx + 1 + -1];
        cout << dynamic_pointer_cast<String>(val)->s << endl;
    }
    {
        uint32_t tpc = *(uint32_t *)(&rom[ctx->pc->i + 8 + 0]);
        uint8_t tmode = *(uint8_t *)(&rom[ctx->pc->i + 8 + 4]);
        ctx->pc->i = tpc;
        ctx->mode = tmode;
    }
}

void func_60(VMCtx *ctx) {
    {
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -1];
        cout << dynamic_pointer_cast<String>(val)->s << endl;
    }
    {
        uint32_t tpc = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint8_t tmode = *(uint8_t *)(&rom[ctx->pc->i + 0 + 4]);
        ctx->pc->i = tpc;
        ctx->mode = tmode;
    }
    ctx->stack_idx += -1;
}

void func_61(VMCtx *ctx) {
    {
        obj_t val = make_shared<Bool>(false);
        ctx->stack[ctx->stack_idx + 0 + 0] = val;
    }
    {
        obj_t val = ctx->stack[ctx->stack_idx + 1 + -1];
        ctx->exit_flag = 1;
        ctx->exit_val = val->clone();
    }
    ctx->stack_idx += 1;
}

void func_62(VMCtx *ctx) {
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -2];
        ctx->mem[dynamic_pointer_cast<Int>(addr)->i] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + -2 + 0] = v;
    }
    ctx->stack_idx += -1;
    ctx->pc->i += 4;
}

void func_63(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 1 + -2];
        ctx->mem[dynamic_pointer_cast<Int>(addr)->i] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + -1 + 0] = v;
    }
    ctx->pc->i += 8;
}

void func_64(VMCtx *ctx) {
    {
        obj_t item = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = make_shared<Int>(item->len());
        ctx->stack[ctx->stack_idx + 0 + -1] = val;
    }
}

void func_65(VMCtx *ctx) {
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 0 + -1] = val;
    }
    {
        obj_t a = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t c = a->lt(b);
        ctx->stack[ctx->stack_idx + 0 + -2] = c;
    }
    ctx->stack_idx += -1;
}

void func_66(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + 1 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 2 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 2 + -1] = val;
    }
    ctx->stack_idx += 2;
    ctx->pc->i += 8;
}

void func_67(VMCtx *ctx) {
    {
        obj_t size = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t start = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -3];
        obj_t sub = dynamic_pointer_cast<String>(val)->substr(start, size);
        ctx->stack[ctx->stack_idx + 0 + -3] = sub;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + -2 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + -1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + -1 + -1] = val;
    }
    ctx->stack_idx += -1;
    ctx->pc->i += 4;
}

void func_68(VMCtx *ctx) {
    {
        obj_t a = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t c = a->equals(b);
        ctx->stack[ctx->stack_idx + 0 + -2] = c;
    }
    ctx->stack_idx += -1;
}

void func_69(VMCtx *ctx) {
    {
        obj_t a = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t c = a->mul(b);
        ctx->stack[ctx->stack_idx + 0 + -2] = c;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + -1 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 0 + -1] = val;
    }
    ctx->pc->i += 4;
}

void func_70(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t a = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 1 + -2];
        obj_t c = a->add(b);
        ctx->stack[ctx->stack_idx + 1 + -2] = c;
    }
    {
        obj_t a = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t c = a->add(b);
        ctx->stack[ctx->stack_idx + 0 + -2] = c;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + -1 + 0] = v;
    }
    ctx->pc->i += 8;
}

void func_71(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 1 + -2];
        ctx->mem[dynamic_pointer_cast<Int>(addr)->i] = val;
    }
    {
        uint32_t tpc = *(uint32_t *)(&rom[ctx->pc->i + 4 + 0]);
        uint8_t tmode = *(uint8_t *)(&rom[ctx->pc->i + 4 + 4]);
        ctx->pc->i = tpc;
        ctx->mode = tmode;
    }
    ctx->stack_idx += -1;
}

void func_72(VMCtx *ctx) {
    {
        obj_t a = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t c = a->equals(b);
        ctx->stack[ctx->stack_idx + 0 + -2] = c;
    }
    {
        obj_t val = ctx->stack[ctx->stack_idx + -1 + -1];
        ctx->exit_flag = 1;
        ctx->exit_val = val->clone();
    }
    ctx->stack_idx += -1;
}

void func_73(VMCtx *ctx) {
    {
        uint32_t size = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        obj_t arr = make_shared<Array>(size);
        ctx->stack[ctx->stack_idx + 0 + 0] = arr;
    }
    ctx->stack_idx += 1;
    ctx->pc->i += 4;
}

void func_74(VMCtx *ctx) {
    {
        obj_t a = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t c = a->lt(b);
        ctx->stack[ctx->stack_idx + 0 + -2] = c;
    }
    ctx->stack_idx += -1;
}

void func_75(VMCtx *ctx) {
    {
        uint32_t tpc = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint8_t tmode = *(uint8_t *)(&rom[ctx->pc->i + 0 + 4]);
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -1];
        if (dynamic_pointer_cast<Bool>(val)->b) { ctx->pc->i = tpc; ctx->mode = tmode; ctx->stack_idx = ctx->stack_idx + 0 - 1; return; }
    }
    ctx->stack_idx += -1;
    ctx->pc->i += 5;
}

void func_76(VMCtx *ctx) {
    {
        obj_t val = make_shared<Bool>(false);
        ctx->stack[ctx->stack_idx + 0 + 0] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 1 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 2 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 2 + -1] = val;
    }
    {
        obj_t idx = ctx->stack[ctx->stack_idx + 2 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 2 + -2];
        obj_t arr = ctx->stack[ctx->stack_idx + 2 + -3];
        dynamic_pointer_cast<Array>(arr)->set(dynamic_pointer_cast<Int>(idx)->i, val);
    }
    ctx->pc->i += 4;
}

void func_77(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + 1 + 0] = v;
    }
    ctx->stack_idx += 2;
    ctx->pc->i += 8;
}

void func_78(VMCtx *ctx) {
    {
        obj_t idx = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t arr = ctx->stack[ctx->stack_idx + 0 + -3];
        dynamic_pointer_cast<Array>(arr)->set(dynamic_pointer_cast<Int>(idx)->i, val);
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + -2 + 0] = v;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + -1 + 0] = v;
    }
    {
        obj_t idx = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t arr = ctx->stack[ctx->stack_idx + 0 + -3];
        dynamic_pointer_cast<Array>(arr)->set(dynamic_pointer_cast<Int>(idx)->i, val);
    }
    ctx->stack_idx += -2;
    ctx->pc->i += 8;
}

void func_79(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + 1 + 0] = v;
    }
    {
        obj_t idx = ctx->stack[ctx->stack_idx + 2 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 2 + -2];
        obj_t arr = ctx->stack[ctx->stack_idx + 2 + -3];
        dynamic_pointer_cast<Array>(arr)->set(dynamic_pointer_cast<Int>(idx)->i, val);
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 8 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    ctx->stack_idx += 1;
    ctx->pc->i += 12;
}

void func_80(VMCtx *ctx) {
    {
        obj_t idx = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t arr = ctx->stack[ctx->stack_idx + 0 + -3];
        dynamic_pointer_cast<Array>(arr)->set(dynamic_pointer_cast<Int>(idx)->i, val);
    }
    ctx->stack_idx += -2;
}

void func_81(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t idx = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 1 + -2];
        obj_t arr = ctx->stack[ctx->stack_idx + 1 + -3];
        dynamic_pointer_cast<Array>(arr)->set(dynamic_pointer_cast<Int>(idx)->i, val);
    }
    ctx->stack_idx += -1;
    ctx->pc->i += 4;
}

void func_82(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t idx = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 1 + -2];
        obj_t arr = ctx->stack[ctx->stack_idx + 1 + -3];
        dynamic_pointer_cast<Array>(arr)->set(dynamic_pointer_cast<Int>(idx)->i, val);
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + -1 + 0] = v;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 8 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    ctx->stack_idx += 1;
    ctx->pc->i += 12;
}

void func_83(VMCtx *ctx) {
    {
        obj_t idx = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t arr = ctx->stack[ctx->stack_idx + 0 + -3];
        dynamic_pointer_cast<Array>(arr)->set(dynamic_pointer_cast<Int>(idx)->i, val);
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + -2 + 0] = v;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + -1 + 0] = v;
    }
    ctx->pc->i += 8;
}

void func_84(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t idx = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 1 + -2];
        obj_t arr = ctx->stack[ctx->stack_idx + 1 + -3];
        dynamic_pointer_cast<Array>(arr)->set(dynamic_pointer_cast<Int>(idx)->i, val);
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + -1 + 0] = v;
    }
    ctx->pc->i += 8;
}

void func_85(VMCtx *ctx) {
    {
        obj_t idx = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t arr = ctx->stack[ctx->stack_idx + 0 + -3];
        dynamic_pointer_cast<Array>(arr)->set(dynamic_pointer_cast<Int>(idx)->i, val);
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + -2 + 0] = v;
    }
    ctx->stack_idx += -1;
    ctx->pc->i += 4;
}

void func_86(VMCtx *ctx) {
    {
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -1];
        ctx->exit_flag = 1;
        ctx->exit_val = val->clone();
    }
}

void func_87(VMCtx *ctx) {
    {
        obj_t size = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t start = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -3];
        obj_t sub = dynamic_pointer_cast<String>(val)->substr(start, size);
        ctx->stack[ctx->stack_idx + 0 + -3] = sub;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + -2 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + -1 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + -1 + -2];
        ctx->mem[dynamic_pointer_cast<Int>(addr)->i] = val;
    }
    ctx->stack_idx += -3;
    ctx->pc->i += 4;
}

void func_88(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    {
        uint32_t sidx = *(uint32_t *)(&rom[ctx->pc->i + 4 + 0]);
        uint32_t key = *(uint32_t *)(&rom[ctx->pc->i + 4 + 4]);
        obj_t sval = make_shared<String>(strtab[sidx]);
        ctx->stack[ctx->stack_idx + 1 + 0] = sval;
    }
    ctx->stack_idx += 2;
    ctx->pc->i += 12;
}

void func_89(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    {
        uint32_t sidx = *(uint32_t *)(&rom[ctx->pc->i + 4 + 0]);
        uint32_t key = *(uint32_t *)(&rom[ctx->pc->i + 4 + 4]);
        obj_t sval = make_shared<String>(strtab[sidx]);
        ctx->stack[ctx->stack_idx + 1 + 0] = sval;
    }
    {
        obj_t a = ctx->stack[ctx->stack_idx + 2 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 2 + -2];
        obj_t c = a->equals(b);
        ctx->stack[ctx->stack_idx + 2 + -2] = c;
    }
    ctx->stack_idx += 1;
    ctx->pc->i += 12;
}

void func_90(VMCtx *ctx) {
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 0 + -1] = val;
    }
    {
        uint32_t sidx = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint32_t key = *(uint32_t *)(&rom[ctx->pc->i + 0 + 4]);
        obj_t sval = make_shared<String>(strtab[sidx]);
        ctx->stack[ctx->stack_idx + 0 + 0] = sval;
    }
    {
        obj_t a = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 1 + -2];
        obj_t c = a->equals(b);
        ctx->stack[ctx->stack_idx + 1 + -2] = c;
    }
    ctx->pc->i += 8;
}

void func_91(VMCtx *ctx) {
    {
        uint32_t tpc = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint8_t tmode = *(uint8_t *)(&rom[ctx->pc->i + 0 + 4]);
        ctx->pc->i = tpc;
        ctx->mode = tmode;
    }
}

void func_92(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    {
        uint32_t tpc = *(uint32_t *)(&rom[ctx->pc->i + 4 + 0]);
        uint8_t tmode = *(uint8_t *)(&rom[ctx->pc->i + 4 + 4]);
        uint8_t nargs = *(uint8_t *)(&rom[ctx->pc->i + 4 + 5]);
        VMCtx inner(tpc, tmode);
        for (int i = 0; i < nargs; ++i) { inner.stack[inner.stack_idx++] = ctx->stack[ctx->stack_idx + 1 - nargs + i]->clone(); }
        obj_t res = inner.run();
        ctx->stack_idx -= nargs;
        ctx->stack[ctx->stack_idx + 1 + 0] = res;
    }
    ctx->stack_idx += 2;
    ctx->pc->i += 10;
}

void func_93(VMCtx *ctx) {
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 0 + -1] = val;
    }
    {
        uint32_t tpc = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint8_t tmode = *(uint8_t *)(&rom[ctx->pc->i + 0 + 4]);
        uint8_t nargs = *(uint8_t *)(&rom[ctx->pc->i + 0 + 5]);
        VMCtx inner(tpc, tmode);
        for (int i = 0; i < nargs; ++i) { inner.stack[inner.stack_idx++] = ctx->stack[ctx->stack_idx + 0 - nargs + i]->clone(); }
        obj_t res = inner.run();
        ctx->stack_idx -= nargs;
        ctx->stack[ctx->stack_idx + 0 + 0] = res;
    }
    ctx->stack_idx += 1;
    ctx->pc->i += 6;
}

void func_94(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 1 + -2];
        ctx->mem[dynamic_pointer_cast<Int>(addr)->i] = val;
    }
    {
        obj_t dict = make_shared<Dict>();
        ctx->stack[ctx->stack_idx + -1 + 0] = dict;
    }
    ctx->pc->i += 4;
}

void func_95(VMCtx *ctx) {
    {
        obj_t size = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t start = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -3];
        obj_t sub = dynamic_pointer_cast<String>(val)->substr(start, size);
        ctx->stack[ctx->stack_idx + 0 + -3] = sub;
    }
    {
        uint32_t sidx = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint32_t key = *(uint32_t *)(&rom[ctx->pc->i + 0 + 4]);
        obj_t sval = make_shared<String>(strtab[sidx]);
        ctx->stack[ctx->stack_idx + -2 + 0] = sval;
    }
    {
        obj_t a = ctx->stack[ctx->stack_idx + -1 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + -1 + -2];
        obj_t c = a->equals(b);
        ctx->stack[ctx->stack_idx + -1 + -2] = c;
    }
    ctx->stack_idx += -2;
    ctx->pc->i += 8;
}

void func_96(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + 1 + 0] = v;
    }
    {
        obj_t a = ctx->stack[ctx->stack_idx + 2 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 2 + -2];
        obj_t c = a->add(b);
        ctx->stack[ctx->stack_idx + 2 + -2] = c;
    }
    ctx->stack_idx += 1;
    ctx->pc->i += 8;
}

void func_97(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t size = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t start = ctx->stack[ctx->stack_idx + 1 + -2];
        obj_t val = ctx->stack[ctx->stack_idx + 1 + -3];
        obj_t sub = dynamic_pointer_cast<String>(val)->substr(start, size);
        ctx->stack[ctx->stack_idx + 1 + -3] = sub;
    }
    {
        uint32_t sidx = *(uint32_t *)(&rom[ctx->pc->i + 4 + 0]);
        uint32_t key = *(uint32_t *)(&rom[ctx->pc->i + 4 + 4]);
        obj_t sval = make_shared<String>(strtab[sidx]);
        ctx->stack[ctx->stack_idx + -1 + 0] = sval;
    }
    {
        obj_t a = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t c = a->equals(b);
        ctx->stack[ctx->stack_idx + 0 + -2] = c;
    }
    ctx->stack_idx += -1;
    ctx->pc->i += 12;
}

void func_98(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + 1 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 2 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 2 + -2];
        ctx->mem[dynamic_pointer_cast<Int>(addr)->i] = val;
    }
    ctx->pc->i += 8;
}

void func_99(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + 1 + 0] = v;
    }
    {
        obj_t size = ctx->stack[ctx->stack_idx + 2 + -1];
        obj_t start = ctx->stack[ctx->stack_idx + 2 + -2];
        obj_t val = ctx->stack[ctx->stack_idx + 2 + -3];
        obj_t sub = dynamic_pointer_cast<String>(val)->substr(start, size);
        ctx->stack[ctx->stack_idx + 2 + -3] = sub;
    }
    ctx->pc->i += 8;
}

void func_100(VMCtx *ctx) {
    {
        uint32_t sidx = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint32_t key = *(uint32_t *)(&rom[ctx->pc->i + 0 + 4]);
        obj_t sval = make_shared<String>(strtab[sidx]);
        ctx->stack[ctx->stack_idx + 0 + 0] = sval;
    }
    {
        obj_t a = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 1 + -2];
        obj_t c = a->equals(b);
        ctx->stack[ctx->stack_idx + 1 + -2] = c;
    }
    {
        uint32_t tpc = *(uint32_t *)(&rom[ctx->pc->i + 8 + 0]);
        uint8_t tmode = *(uint8_t *)(&rom[ctx->pc->i + 8 + 4]);
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -1];
        if (dynamic_pointer_cast<Bool>(val)->b) { ctx->pc->i = tpc; ctx->mode = tmode; ctx->stack_idx = ctx->stack_idx + 0 - 1; return; }
    }
    ctx->stack_idx += -1;
    ctx->pc->i += 13;
}

void func_101(VMCtx *ctx) {
    {
        uint32_t a = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint32_t b = *(uint32_t *)(&rom[ctx->pc->i + 0 + 4]);
        obj_t x = ctx->stack[ctx->stack_idx + 0 - a];
        obj_t y = ctx->stack[ctx->stack_idx + 0 - b];
        ctx->stack[ctx->stack_idx + 0 - b] = x;
        ctx->stack[ctx->stack_idx + 0 - a] = y;
    }
    ctx->pc->i += 8;
}

void func_102(VMCtx *ctx) {
    {
        obj_t a = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t c = a->sub(b);
        ctx->stack[ctx->stack_idx + 0 + -2] = c;
    }
    ctx->stack_idx += -1;
}

void func_103(VMCtx *ctx) {
    {
        obj_t size = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t start = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -3];
        obj_t sub = dynamic_pointer_cast<String>(val)->substr(start, size);
        ctx->stack[ctx->stack_idx + 0 + -3] = sub;
    }
    ctx->stack_idx += -2;
}

void func_104(VMCtx *ctx) {
    {
        obj_t a = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t c = a->add(b);
        ctx->stack[ctx->stack_idx + 0 + -2] = c;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + -1 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -2];
        ctx->mem[dynamic_pointer_cast<Int>(addr)->i] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + -2 + 0] = v;
    }
    ctx->stack_idx += -1;
    ctx->pc->i += 8;
}

void func_105(VMCtx *ctx) {
    {
        obj_t item = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = make_shared<Int>(item->len());
        ctx->stack[ctx->stack_idx + 0 + -1] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    {
        uint32_t a = *(uint32_t *)(&rom[ctx->pc->i + 4 + 0]);
        uint32_t b = *(uint32_t *)(&rom[ctx->pc->i + 4 + 4]);
        obj_t x = ctx->stack[ctx->stack_idx + 1 - a];
        obj_t y = ctx->stack[ctx->stack_idx + 1 - b];
        ctx->stack[ctx->stack_idx + 1 - b] = x;
        ctx->stack[ctx->stack_idx + 1 - a] = y;
    }
    ctx->stack_idx += 1;
    ctx->pc->i += 12;
}

void func_106(VMCtx *ctx) {
    {
        obj_t a = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t c = a->sub(b);
        ctx->stack[ctx->stack_idx + 0 + -2] = c;
    }
    {
        obj_t size = ctx->stack[ctx->stack_idx + -1 + -1];
        obj_t start = ctx->stack[ctx->stack_idx + -1 + -2];
        obj_t val = ctx->stack[ctx->stack_idx + -1 + -3];
        obj_t sub = dynamic_pointer_cast<String>(val)->substr(start, size);
        ctx->stack[ctx->stack_idx + -1 + -3] = sub;
    }
    ctx->stack_idx += -3;
}

void func_107(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t idx = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t arr = ctx->stack[ctx->stack_idx + 1 + -2];
        obj_t val = dynamic_pointer_cast<Array>(arr)->get(dynamic_pointer_cast<Int>(idx)->i);
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    ctx->stack_idx += 1;
    ctx->pc->i += 4;
}

void func_108(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    {
        obj_t a = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 1 + -2];
        obj_t c = a->add(b);
        ctx->stack[ctx->stack_idx + 1 + -2] = c;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    ctx->stack_idx += 1;
    ctx->pc->i += 8;
}

void func_109(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t idx = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t arr = ctx->stack[ctx->stack_idx + 1 + -2];
        obj_t val = dynamic_pointer_cast<Array>(arr)->get(dynamic_pointer_cast<Int>(idx)->i);
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + 1 + 0] = v;
    }
    ctx->stack_idx += 2;
    ctx->pc->i += 8;
}

void func_110(VMCtx *ctx) {
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -2];
        ctx->mem[dynamic_pointer_cast<Int>(addr)->i] = val;
    }
    {
    }
    ctx->stack_idx += -3;
}

void func_111(VMCtx *ctx) {
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 0 + -1] = val;
    }
    {
        obj_t key = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t dict = ctx->stack[ctx->stack_idx + 0 + -3];
        dynamic_pointer_cast<Dict>(dict)->set(dynamic_pointer_cast<String>(key)->s, val);
    }
    ctx->stack_idx += -2;
}

void func_112(VMCtx *ctx) {
    {
    }
    ctx->stack_idx += -1;
}

void func_113(VMCtx *ctx) {
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 0 + -1] = val;
    }
    {
        uint32_t sidx = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint32_t key = *(uint32_t *)(&rom[ctx->pc->i + 0 + 4]);
        obj_t sval = make_shared<String>(strtab[sidx]);
        ctx->stack[ctx->stack_idx + 0 + 0] = sval;
    }
    ctx->stack_idx += 1;
    ctx->pc->i += 8;
}

void func_114(VMCtx *ctx) {
    {
        obj_t a = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t c = a->equals(b);
        ctx->stack[ctx->stack_idx + 0 + -2] = c;
    }
    {
        uint32_t tpc = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint8_t tmode = *(uint8_t *)(&rom[ctx->pc->i + 0 + 4]);
        obj_t val = ctx->stack[ctx->stack_idx + -1 + -1];
        if (dynamic_pointer_cast<Bool>(val)->b) { ctx->pc->i = tpc; ctx->mode = tmode; ctx->stack_idx = ctx->stack_idx + -1 - 1; return; }
    }
    ctx->stack_idx += -2;
    ctx->pc->i += 5;
}

void func_115(VMCtx *ctx) {
    {
        uint32_t sidx = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint32_t key = *(uint32_t *)(&rom[ctx->pc->i + 0 + 4]);
        obj_t sval = make_shared<String>(strtab[sidx]);
        ctx->stack[ctx->stack_idx + 0 + 0] = sval;
    }
    {
        obj_t val = ctx->stack[ctx->stack_idx + 1 + -1];
        cout << dynamic_pointer_cast<String>(val)->s << endl;
    }
    {
        ctx->exit_flag = 1;
        ctx->exit_val = make_shared<Void>();
    }
}

void func_116(VMCtx *ctx) {
    {
        uint32_t size = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        obj_t arr = make_shared<Array>(size);
        ctx->stack[ctx->stack_idx + 0 + 0] = arr;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + 1 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 2 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 2 + -1] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 8 + 0]));
        ctx->stack[ctx->stack_idx + 2 + 0] = v;
    }
    ctx->stack_idx += 3;
    ctx->pc->i += 12;
}

void func_117(VMCtx *ctx) {
    {
        obj_t idx = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t arr = ctx->stack[ctx->stack_idx + 0 + -3];
        dynamic_pointer_cast<Array>(arr)->set(dynamic_pointer_cast<Int>(idx)->i, val);
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + -2 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + -1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + -1 + -1] = val;
    }
    ctx->stack_idx += -1;
    ctx->pc->i += 4;
}

void func_118(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t idx = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 1 + -2];
        obj_t arr = ctx->stack[ctx->stack_idx + 1 + -3];
        dynamic_pointer_cast<Array>(arr)->set(dynamic_pointer_cast<Int>(idx)->i, val);
    }
    {
        obj_t val = ctx->stack[ctx->stack_idx + -1 + -1];
        ctx->exit_flag = 1;
        ctx->exit_val = val->clone();
    }
    ctx->stack_idx += -1;
}

void func_119(VMCtx *ctx) {
    {
        uint32_t size = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        obj_t arr = make_shared<Array>(size);
        ctx->stack[ctx->stack_idx + 0 + 0] = arr;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + 1 + 0] = v;
    }
    ctx->stack_idx += 2;
    ctx->pc->i += 8;
}

void func_120(VMCtx *ctx) {
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -2];
        ctx->mem[dynamic_pointer_cast<Int>(addr)->i] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + -2 + 0] = v;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + -1 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -2];
        ctx->mem[dynamic_pointer_cast<Int>(addr)->i] = val;
    }
    ctx->stack_idx += -2;
    ctx->pc->i += 8;
}

void func_121(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + 1 + 0] = v;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 8 + 0]));
        ctx->stack[ctx->stack_idx + 2 + 0] = v;
    }
    ctx->stack_idx += 3;
    ctx->pc->i += 12;
}

void func_122(VMCtx *ctx) {
    {
        uint32_t sidx = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint32_t key = *(uint32_t *)(&rom[ctx->pc->i + 0 + 4]);
        obj_t sval = make_shared<String>(strtab[sidx]);
        ctx->stack[ctx->stack_idx + 0 + 0] = sval;
    }
    {
        obj_t a = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 1 + -2];
        obj_t c = a->equals(b);
        ctx->stack[ctx->stack_idx + 1 + -2] = c;
    }
    {
        uint32_t tpc = *(uint32_t *)(&rom[ctx->pc->i + 8 + 0]);
        uint8_t tmode = *(uint8_t *)(&rom[ctx->pc->i + 8 + 4]);
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -1];
        if (!dynamic_pointer_cast<Bool>(val)->b) { ctx->pc->i = tpc; ctx->mode = tmode; ctx->stack_idx = ctx->stack_idx + 0 - 1; return; }
    }
    ctx->stack_idx += -1;
    ctx->pc->i += 13;
}

void func_123(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    {
        uint32_t a = *(uint32_t *)(&rom[ctx->pc->i + 4 + 0]);
        uint32_t b = *(uint32_t *)(&rom[ctx->pc->i + 4 + 4]);
        obj_t x = ctx->stack[ctx->stack_idx + 1 - a];
        obj_t y = ctx->stack[ctx->stack_idx + 1 - b];
        ctx->stack[ctx->stack_idx + 1 - b] = x;
        ctx->stack[ctx->stack_idx + 1 - a] = y;
    }
    {
        obj_t a = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 1 + -2];
        obj_t c = a->sub(b);
        ctx->stack[ctx->stack_idx + 1 + -2] = c;
    }
    ctx->pc->i += 12;
}

void func_124(VMCtx *ctx) {
    {
        obj_t size = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t start = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -3];
        obj_t sub = dynamic_pointer_cast<String>(val)->substr(start, size);
        ctx->stack[ctx->stack_idx + 0 + -3] = sub;
    }
    {
        uint32_t tpc = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint8_t tmode = *(uint8_t *)(&rom[ctx->pc->i + 0 + 4]);
        uint8_t nargs = *(uint8_t *)(&rom[ctx->pc->i + 0 + 5]);
        VMCtx inner(tpc, tmode);
        for (int i = 0; i < nargs; ++i) { inner.stack[inner.stack_idx++] = ctx->stack[ctx->stack_idx + -2 - nargs + i]->clone(); }
        obj_t res = inner.run();
        ctx->stack_idx -= nargs;
        ctx->stack[ctx->stack_idx + -2 + 0] = res;
    }
    ctx->stack_idx += -1;
    ctx->pc->i += 6;
}

void func_125(VMCtx *ctx) {
    {
        obj_t idx = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t arr = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t val = dynamic_pointer_cast<Array>(arr)->get(dynamic_pointer_cast<Int>(idx)->i);
        ctx->stack[ctx->stack_idx + 0 + -1] = val;
    }
}

void func_126(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 1 + -2];
        ctx->mem[dynamic_pointer_cast<Int>(addr)->i] = val;
    }
    {
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + -2 + 0] = v;
    }
    ctx->stack_idx += -1;
    ctx->pc->i += 8;
}

void func_127(VMCtx *ctx) {
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 0 + -1] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    {
        obj_t val = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t arr = ctx->stack[ctx->stack_idx + 1 + -2];
        dynamic_pointer_cast<Array>(arr)->append(val);
    }
    ctx->pc->i += 4;
}

void func_128(VMCtx *ctx) {
    {
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -1];
        cout << dynamic_pointer_cast<String>(val)->s << endl;
    }
    {
        ctx->exit_flag = 1;
        ctx->exit_val = make_shared<Void>();
    }
    ctx->stack_idx += -1;
}

void func_129(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 1 + -2];
        ctx->mem[dynamic_pointer_cast<Int>(addr)->i] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + -1 + 0] = v;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 8 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    ctx->stack_idx += 1;
    ctx->pc->i += 12;
}

void func_130(VMCtx *ctx) {
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -2];
        ctx->mem[dynamic_pointer_cast<Int>(addr)->i] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + -2 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + -1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + -1 + -1] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + -1 + 0] = v;
    }
    ctx->pc->i += 8;
}

void func_131(VMCtx *ctx) {
    {
        obj_t a = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t c = a->add(b);
        ctx->stack[ctx->stack_idx + 0 + -2] = c;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + -1 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -2];
        ctx->mem[dynamic_pointer_cast<Int>(addr)->i] = val;
    }
    ctx->stack_idx += -2;
    ctx->pc->i += 4;
}

void func_132(VMCtx *ctx) {
    {
        obj_t size = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t start = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t val = ctx->stack[ctx->stack_idx + 0 + -3];
        obj_t sub = dynamic_pointer_cast<String>(val)->substr(start, size);
        ctx->stack[ctx->stack_idx + 0 + -3] = sub;
    }
    {
        uint32_t sidx = *(uint32_t *)(&rom[ctx->pc->i + 0 + 0]);
        uint32_t key = *(uint32_t *)(&rom[ctx->pc->i + 0 + 4]);
        obj_t sval = make_shared<String>(strtab[sidx]);
        ctx->stack[ctx->stack_idx + -2 + 0] = sval;
    }
    {
        obj_t a = ctx->stack[ctx->stack_idx + -1 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + -1 + -2];
        obj_t c = a->equals(b);
        ctx->stack[ctx->stack_idx + -1 + -2] = c;
    }
    {
        uint32_t tpc = *(uint32_t *)(&rom[ctx->pc->i + 8 + 0]);
        uint8_t tmode = *(uint8_t *)(&rom[ctx->pc->i + 8 + 4]);
        obj_t val = ctx->stack[ctx->stack_idx + -2 + -1];
        if (dynamic_pointer_cast<Bool>(val)->b) { ctx->pc->i = tpc; ctx->mode = tmode; ctx->stack_idx = ctx->stack_idx + -2 - 1; return; }
    }
    ctx->stack_idx += -3;
    ctx->pc->i += 13;
}

void func_133(VMCtx *ctx) {
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 0 + -1] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t a = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 1 + -2];
        obj_t c = a->add(b);
        ctx->stack[ctx->stack_idx + 1 + -2] = c;
    }
    ctx->pc->i += 4;
}

void func_134(VMCtx *ctx) {
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 0 + -1] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + 1 + 0] = v;
    }
    ctx->stack_idx += 2;
    ctx->pc->i += 8;
}

void func_135(VMCtx *ctx) {
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 0 + -1] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        uint32_t a = *(uint32_t *)(&rom[ctx->pc->i + 4 + 0]);
        uint32_t b = *(uint32_t *)(&rom[ctx->pc->i + 4 + 4]);
        obj_t x = ctx->stack[ctx->stack_idx + 1 - a];
        obj_t y = ctx->stack[ctx->stack_idx + 1 - b];
        ctx->stack[ctx->stack_idx + 1 - b] = x;
        ctx->stack[ctx->stack_idx + 1 - a] = y;
    }
    ctx->stack_idx += 1;
    ctx->pc->i += 12;
}

void func_136(VMCtx *ctx) {
    {
        obj_t a = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 0 + -2];
        obj_t c = a->sub(b);
        ctx->stack[ctx->stack_idx + 0 + -2] = c;
    }
    {
        obj_t size = ctx->stack[ctx->stack_idx + -1 + -1];
        obj_t start = ctx->stack[ctx->stack_idx + -1 + -2];
        obj_t val = ctx->stack[ctx->stack_idx + -1 + -3];
        obj_t sub = dynamic_pointer_cast<String>(val)->substr(start, size);
        ctx->stack[ctx->stack_idx + -1 + -3] = sub;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + -3 + 0] = v;
    }
    ctx->stack_idx += -2;
    ctx->pc->i += 4;
}

void func_137(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t idx = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 1 + -2];
        obj_t arr = ctx->stack[ctx->stack_idx + 1 + -3];
        dynamic_pointer_cast<Array>(arr)->set(dynamic_pointer_cast<Int>(idx)->i, val);
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + -1 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 0 + -1] = val;
    }
    ctx->pc->i += 8;
}

void func_138(VMCtx *ctx) {
    {
        obj_t s = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = dynamic_pointer_cast<String>(s)->value();
        ctx->stack[ctx->stack_idx + 0 + -1] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        uint32_t a = *(uint32_t *)(&rom[ctx->pc->i + 4 + 0]);
        uint32_t b = *(uint32_t *)(&rom[ctx->pc->i + 4 + 4]);
        obj_t x = ctx->stack[ctx->stack_idx + 1 - a];
        obj_t y = ctx->stack[ctx->stack_idx + 1 - b];
        ctx->stack[ctx->stack_idx + 1 - b] = x;
        ctx->stack[ctx->stack_idx + 1 - a] = y;
    }
    {
        obj_t a = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 1 + -2];
        obj_t c = a->sub(b);
        ctx->stack[ctx->stack_idx + 1 + -2] = c;
    }
    ctx->pc->i += 12;
}

void func_139(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 4 + 0]));
        ctx->stack[ctx->stack_idx + 1 + 0] = v;
    }
    {
        obj_t a = ctx->stack[ctx->stack_idx + 2 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 2 + -2];
        obj_t c = a->mul(b);
        ctx->stack[ctx->stack_idx + 2 + -2] = c;
    }
    ctx->stack_idx += 1;
    ctx->pc->i += 8;
}

void func_140(VMCtx *ctx) {
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 1 + -1] = val;
    }
    {
        obj_t a = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t b = ctx->stack[ctx->stack_idx + 1 + -2];
        obj_t c = a->add(b);
        ctx->stack[ctx->stack_idx + 1 + -2] = c;
    }
    ctx->pc->i += 4;
}

void func_141(VMCtx *ctx) {
    {
        obj_t addr = ctx->stack[ctx->stack_idx + 0 + -1];
        obj_t val = ctx->mem[dynamic_pointer_cast<Int>(addr)->i];
        ctx->stack[ctx->stack_idx + 0 + -1] = val;
    }
    {
        obj_t v = make_shared<Int>(*(uint32_t *)(&rom[ctx->pc->i + 0 + 0]));
        ctx->stack[ctx->stack_idx + 0 + 0] = v;
    }
    {
        obj_t idx = ctx->stack[ctx->stack_idx + 1 + -1];
        obj_t val = ctx->stack[ctx->stack_idx + 1 + -2];
        obj_t arr = ctx->stack[ctx->stack_idx + 1 + -3];
        dynamic_pointer_cast<Array>(arr)->set(dynamic_pointer_cast<Int>(idx)->i, val);
    }
    {
        obj_t val = ctx->stack[ctx->stack_idx + -1 + -1];
        ctx->exit_flag = 1;
        ctx->exit_val = val->clone();
    }
    ctx->stack_idx += -1;
}

vm_func_t functions[] = {func_0,func_1,func_2,func_3,func_4,func_5,func_6,func_7,func_8,func_9,func_10,func_11,func_12,func_13,func_14,func_15,func_16,func_17,func_18,func_19,func_20,func_21,func_22,func_23,func_24,func_25,func_26,func_27,func_28,func_29,func_30,func_31,func_32,func_33,func_34,func_35,func_36,func_37,func_38,func_39,func_40,func_41,func_42,func_43,func_44,func_45,func_46,func_47,func_48,func_49,func_50,func_51,func_52,func_53,func_54,func_55,func_56,func_57,func_58,func_59,func_60,func_61,func_62,func_63,func_64,func_65,func_66,func_67,func_68,func_69,func_70,func_71,func_72,func_73,func_74,func_75,func_76,func_77,func_78,func_79,func_80,func_81,func_82,func_83,func_84,func_85,func_86,func_87,func_88,func_89,func_90,func_91,func_92,func_93,func_94,func_95,func_96,func_97,func_98,func_99,func_100,func_101,func_102,func_103,func_104,func_105,func_106,func_107,func_108,func_109,func_110,func_111,func_112,func_113,func_114,func_115,func_116,func_117,func_118,func_119,func_120,func_121,func_122,func_123,func_124,func_125,func_126,func_127,func_128,func_129,func_130,func_131,func_132,func_133,func_134,func_135,func_136,func_137,func_138,func_139,func_140,func_141};
