#include "main.h"

char originalImageCode;
evImgCover evCover;

int main() {
    std::ios::sync_with_stdio(false);
    //std::string a = ".//";
    //std::string b = "ev101_aa";
    //std::string res = a + b;
    evCover.SetFileAfterFix("a");
    evCover.fun();
    evCover.SetFileAfterFix("_a");
    evCover.fun();
    evCover.SetFileAfterFix("_mm");
    evCover.fun();
    evCover.SetFileAfterFix("mm");
    evCover.fun();
    return 0;
}