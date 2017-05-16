// http://cpptruths.blogspot.com/2011/07/compile-time-regex-matcher-using.html

constexpr int
match_c(const char *regexp, const char *text);
constexpr int
matchhere_c(const char *regexp, const char *text);
constexpr int
matchstar_c(int c, const char *regexp, const char *text);
constexpr int
matchend_c(const char *regexp, const char *text);

constexpr int
matchend_c(const char *regexp, const char *text) {
   return matchhere_c(regexp, text) ? 1 : (*text == '\0') ? 0 : matchend_c(regexp, text + 1);
}

constexpr int
match_c(const char *regexp, const char *text) {
   return (regexp[0] == '^') ? matchhere_c(regexp + 1, text) : matchend_c(regexp, text);
}

/* matchhere: search for regexp at beginning of text */
constexpr int
matchhere_c(const char *regexp, const char *text) {
   return (regexp[0] == '\0')
              ? 1
              : (regexp[1] == '*')
                    ? matchstar_c(regexp[0], regexp + 2, text)
                    : (regexp[0] == '$' && regexp[1] == '\0')
                          ? (*text == '\0')
                          : (*text != '\0' && (regexp[0] == '.' || regexp[0] == *text)) ? matchhere_c(regexp + 1, text + 1) : 0;
}

/* matchstar: search for c*regexp at beginning of text */
constexpr int
matchstar_c(int c, const char *regexp, const char *text) {
   return matchhere_c(regexp, text) ? 1 : (*text != '\0' && (*text == c || c == '.')) ? matchstar_c(c, regexp, text + 1) : 0;
}

int
main(void) {
   static_assert(match_c("^T.*TS$", "TEXTS"), "...");

   return 0;
}
