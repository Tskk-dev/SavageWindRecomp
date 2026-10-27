// clang -O2 tools/test_glsl_fold_ipa_w.c -o build/test_glsl_fold_ipa_w
#include <assert.h>
#include "../runtime/nvn/maxwell/translate.c"

int main(void) {
    char text[] = "abc = def\nreturn;";
    assert(glsl_span_find(text, 9, " = ", 3) == text + 3);
    assert(glsl_span_find(text, 9, "return;", 7) == NULL);
    assert(glsl_span_find(text, 5, " = ", 3) == NULL);
    assert(glsl_span_find(text, 0, "a", 1) == NULL);
    assert(glsl_span_find(text, 0, "", 0) == text);

    const char *source = "    r0 = as_u(gl_FragCoord[3]);\n"
                         "    r1 = floatBitsToUint((1.0f / uintBitsToFloat(r0)));\n"
                         "    r2 = as_u(v0[0] * gl_FragCoord.w * uintBitsToFloat(r1));\n";
    Str body = {0};
    sp(&body, "%s", source);
    glsl_fold_ipa_w(&body);
    assert(strstr(body.buf, "r2 = as_u(v0[0]);"));
    free(body.buf);

    body = (Str){0};
    sp(&body, "    break;\n%s", source);
    glsl_fold_ipa_w(&body);
    assert(strstr(body.buf, "v0[0] * gl_FragCoord.w * uintBitsToFloat(r1)"));
    free(body.buf);
    puts("PASS: bounded search and IPA folding / break guard");
    return 0;
}
