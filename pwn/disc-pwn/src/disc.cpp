
#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include "stdlib.h"
#include <cassert>
#include <cstring>
#include <cstdio>

// #define DEBUG 1

using namespace std;

struct Object;
typedef shared_ptr<Object> obj_t;

// 0: void
// 1: bool
// 2: int
// 3: string
// 4: array
// 5: dict

struct Object {
    virtual obj_t add(obj_t other) {}
    virtual obj_t sub(obj_t other) {}
    virtual obj_t mul(obj_t other) {}
    virtual obj_t equals(obj_t other) {}
    virtual obj_t lt(obj_t other) {}
    #ifdef DEBUG
    virtual string pretty() {
        return string("<object>");
    }
    #endif
    virtual uint32_t len() {}

    virtual obj_t clone() {}
    virtual uint32_t type() {}
};

struct Bool : Object {
    bool b;

    Bool(bool _b): b(_b) {}

    obj_t equals(obj_t other) {
        auto tb = dynamic_pointer_cast<Bool>(other);
        return make_shared<Bool>(this->b == tb->b);
    }

    obj_t clone() {
        return make_shared<Bool>(this->b);
    }

    #ifdef DEBUG
    string pretty() {
        return string(b ? "true" : "false");
    }
    #endif

    uint32_t type() {
        return 1;
    }
};

struct Array : Object {
    vector<obj_t> dat;

    Array(uint32_t size) {
        dat.resize(size);
    }

    Array(vector<obj_t> _dat): dat(_dat) {}

    obj_t get(int key) {
        return dat[key];
    }

    void set(int key, obj_t val) {
        dat[key] = val;
    }

    uint32_t len() {
        return dat.size();
    }

    void append(obj_t val) {
        dat.push_back(val);
    }

    obj_t clone() {
        vector<obj_t> other;
        for (auto t : this->dat) {
            other.push_back(t->clone());
        }
        return make_shared<Array>(other);
    }

    #ifdef DEBUG
    string pretty() {
        string p;
        p.append("[");
        for (int i = 0; i < dat.size(); ++i) {
            obj_t t = dat[i];
            if (t) {
                p += dat[i]->pretty();
            } else {
                p.append("null");
            }
            if (i < dat.size() - 1) {
                p.append(", ");
            }
        }
        p.append("]");
        return p;
    }
    #endif

    uint32_t type() {
        return 4;
    }
};

struct Int : Object {
    Int(uint32_t _i): i(_i) {}

    uint32_t i;

    obj_t add(obj_t other) {
        auto t = dynamic_pointer_cast<Int>(other);
        // if (this->i == 128) {
        //     cout << "Adding to: " << t->i << endl;
        // }
        return make_shared<Int>(this->i + t->i);
    }

    obj_t sub(obj_t other) {
        auto t = dynamic_pointer_cast<Int>(other);
        return make_shared<Int>(this->i - t->i);
    }

    obj_t mul(obj_t other) {
        auto t = dynamic_pointer_cast<Int>(other);
        return make_shared<Int>(this->i * t->i);
    }

    obj_t equals(obj_t other) {
        auto tb = dynamic_pointer_cast<Int>(other);
        return make_shared<Bool>(this->i == tb->i);
    }

    obj_t lt(obj_t other) {
        auto tb = dynamic_pointer_cast<Int>(other);
        return make_shared<Bool>(this->i < tb->i);
    }

    obj_t clone() {
        return make_shared<Int>(this->i);
    }

    #ifdef DEBUG
    string pretty() {
        return to_string(i);
    }
    #endif

    uint32_t type() {
        return 2;
    }
};

struct String : Object {
    String(string _s): s(_s) {}

    string s;

    uint32_t len() {
        return s.size();
    }

    obj_t equals(obj_t other) {
        auto tb = dynamic_pointer_cast<String>(other);
        return make_shared<Bool>(this->s.compare(tb->s) == 0);
    }

    obj_t substr(obj_t start, obj_t size) {
        string sub = s.substr(dynamic_pointer_cast<Int>(start)->i, dynamic_pointer_cast<Int>(size)->i);
        return make_shared<String>(sub);
    }

    obj_t value() {
        assert(s.size() == 1);
        uint8_t x = s[0];
        return make_shared<Int>((int32_t)x);
    }

    obj_t clone() {
        return make_shared<String>(this->s);
    }

    #ifdef DEBUG
    string pretty() {
        string p;
        p.append("\"");
        p += s;
        p.append("\"");
        return p;
    }
    #endif

    uint32_t type() {
        return 3;
    }
};

struct Dict : Object {
    unordered_map<string, shared_ptr<Object>> named;

    Dict(): named() {}

    Dict(unordered_map<string, obj_t> _named): named(_named) {}

    shared_ptr<Object> get(string key) {
        return named.at(key);
    }

    obj_t has(string key) {
        return make_shared<Bool>(named.count(key) == 1);
    }

    void set(string key, shared_ptr<Object> val) {
        named.insert({key, val});
    }

    obj_t keys() {
        auto arr = make_shared<Array>(named.size());
        int idx = 0;
        for (auto it = named.begin(); it != named.end(); ++it) {
            arr->dat[idx++] = make_shared<String>(it->first);
        }
        return arr;
    }

    obj_t clone() {
        unordered_map<string, obj_t> other;
        for (auto it = named.begin(); it != named.end(); it++) {
            other.insert({it->first, it->second->clone()});
        }
        return make_shared<Dict>(other);
    }

    #ifdef DEBUG
    string pretty() {
        string p;
        p.append("{");
        for (auto it = named.begin(); it != named.end(); ++it) {
            p.append("\"");
            p += it->first;
            p.append("\": ");
            p += it->second->pretty();
            p.append(", ");
        }
        p = p.substr(0, p.length() - 2);
        p.append("}");
        return p;
    }
    #endif

    uint32_t type() {
        return 5;
    }
};

struct Void : Object {
    obj_t clone() {
        return make_shared<Void>();
    }

    #ifdef DEBUG
    string pretty() {
        return string("<void>");
    }
    #endif

    uint32_t type() {
        return 0;
    }
};

struct VMCtx;

typedef void (*vm_func_t)(VMCtx *);

uint8_t *rom;

#include "strtab.h"

struct VMCtx {
    uint32_t exit_flag;
    obj_t exit_val;

    shared_ptr<Int> pc;
    uint8_t mode;

    uint32_t stack_idx;
    obj_t stack[0x100];

    obj_t mem[0x100];

    VMCtx(uint32_t _pc, uint8_t _mode): pc(make_shared<Int>(_pc)), mode(_mode), exit_flag(0), stack_idx(0) {}

    #ifdef DEBUG
    void print_info(uint32_t sp_adjust) {
        cout << "================" << endl;
        cout << "pc: " << this->pc->i << endl;
        cout << "stack:" << endl;
        for (int i = 0; i < this->stack_idx + sp_adjust; ++i) {
            obj_t t = this->stack[i];
            cout << "[" << i << "]: " << (t ? t->pretty() : "null") << endl;
        }
        cout << "mem:" << endl;
        for (int i = 0; i < 0x100; ++i) {
            obj_t t = this->mem[i];
            if (t) {
                cout << "M[" << i << "]: " << t->pretty() << endl;
            }
        }
        cout << "================" << endl;
    }

    void debug(uint32_t sp_adjust) {
        print_info(sp_adjust);
        flush(cout);
    }
    #endif

    obj_t run();
};

#include "ops.h"

obj_t VMCtx::run() {
    // cout << "Spawned new vm: " << this << endl;
    while (!this->exit_flag) {
        uint8_t op = rom[this->pc->i];

        // cout << this->pc->i << " -> " << (uint32_t)op << endl;

        // if (op == 142) {
        //     this->debug(0);
        // }

        uint8_t fidx = op;
        this->pc->i += 1;

        vm_func_t func = functions[fidx];
        func(this);
    }
    // cout << "Exit flag is: " << this->exit_flag << endl;
    // cout << "Returning from vm: " << this->exit_val->pretty() << endl;
    return this->exit_val;
}


int main() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    const char *flag = getenv("FLAG");
    if (!flag) {
        flag = "PWN_FLAG_WILL_BE_IN_ENV";
    }

    FILE *f = fopen("./rom.dat", "rb");
    fseek(f, 0, SEEK_END);
    size_t len = ftell(f);
    fseek(f, 0, SEEK_SET);
    rom = (uint8_t *)malloc(len);
    fread(rom, 1, len, f);

    auto d = make_shared<Dict>();
    d->set("pls_dont_read", make_shared<String>(flag));

    VMCtx ctx(0, 0);
    ctx.mem[42] = d;
    ctx.run();
}
