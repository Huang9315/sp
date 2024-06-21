#include "compiler.h"

#define TMAX 10000000
#define LMAX 100

char *typeName[6] = {"Id", "Int", "Keyword", "Literal", "Char", "Op"};
char code[TMAX], *p;
char strTable[TMAX], *strTableEnd = strTable;
char *tokens[TMAX], tokenTop = 0, tokenIdx = 0, token[LMAX];

char *scan() {
    while (isspace(*p)) p++;

    char *start = p;
    int type;
    if (*p == '\0') return NULL;
    if (*p == '"') {
        p++;
        while (*p != '"' && *p != '\0') p++;
        if (*p == '"') p++;
        type = Literal;
    } else if (isDigit(*p)) {
        while (isDigit(*p)) p++;
        type = Int;
    } else if (isAlpha(*p) || *p == '_') {
        while (isAlpha(*p) || isDigit(*p) || *p == '_') p++;
        type = Id;
    } else if (strchr("+-*/%&|<>!=", *p) != NULL) {
        char c = *p++;
        if (*p == '=') p++;
        else if (strchr("+-&|", c) != NULL && *p == c) p++;
        type = Op;
    } else {
        p++;
        type = Char;
    }

    int len = p - start;
    if (len >= LMAX) {
        fprintf(stderr, "Token length exceeds limit: %.*s\n", len, start);
        exit(1);
    }
    strncpy(token, start, len);
    token[len] = '\0';
    types[tokenTop] = type;
    return token;
}

void lex(char *code) {
    printf("========== lex ==============\n");
    p = code;
    tokenTop = 0;
    while (1) {
        char *tok = scan();
        if (tok == NULL) break;
        strcpy(strTableEnd, tok);
        tokens[tokenTop++] = strTableEnd;
        strTableEnd += (strlen(tok) + 1);
        printf("token=%s, type=%s\n", tok, typeName[types[tokenTop - 1]]);
    }
}


void DOWHILE() {
    int doBegin = nextLabel();
    int doEnd = nextLabel();
    emit("(L%d)\n", doBegin);
    skip("do");
    STMT();
    emit("(L%d)\n", doEnd);
    skip("while");
    skip("(");
    int e = E();
    emit("if not T%d goto L%d\n", e, doBegin);
    skip(")");
    skip(";");
    emit("goto L%d\n", doBegin);
    emit("(L%d)\n", doEnd);
}

void STMT() {
    if (isNext("while"))
        WHILE();
    else if (isNext("do"))
        DOWHILE();
    else if (isNext("if"))
        IF();
    else if (isNext("{"))
        BLOCK();
    else
        ASSIGN();
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <source file>\n", argv[0]);
        return 1;
    }

    int len = readText(argv[1], code, TMAX);
    if (len < 0) {
        return 1;
    }

    puts(code);
    lex(code);
    dump(tokens, tokenTop);
    parse();

    return 0;
}
