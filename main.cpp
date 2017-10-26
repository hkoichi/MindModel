#include <iostream>

using namespace std;

enum NextInputType {
    SOME_OR_ALL_OR_NO,
    NAME,
    ARE
};

enum PartnerType {
    ALL,
    SOME,
    NO
};

class Pair {
public:
    string peoples[2];
    PartnerType people1Type;
    bool notFlg = false;
};

Pair pairs[2];

bool loadConditions();
bool loadCommonPeople();

int main() {
    // 読み込み
    if (!loadConditions()) {
        cout << "syntax error" << endl;
        return -1;
    }
    // 共通の職種をpairs[0]のpeoples[1]、pairs[1]のpeoples[0]にくるようにする
    if (loadCommonPeople()) {
        cout << pairs[0].peoples[0] << "     " << pairs[0].peoples[1] << "     " << pairs[1].peoples[1] << endl;
    }else {
        cout << "there is no common people" << endl;
        return -1;


    }
    return 0;
}

bool loadCommonPeople() {
    bool ans = false;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (pairs[0].peoples[i] == pairs[1].peoples[j]){
                if (i == 0) {
                    string temp = pairs[0].peoples[0];
                    pairs[0].peoples[0] = pairs[0].peoples[1];
                    pairs[0].peoples[1] = temp;
                }
                if (j == 1) {
                    string temp = pairs[1].peoples[0];
                    pairs[1].peoples[0] = pairs[1].peoples[1];
                    pairs[1].peoples[1] = temp;
                }
                ans = true;
            }
        }
    }
    return ans;
}

bool loadConditions() {
    for (int i = 0; i < 2; i++) {
        if (i == 1) {
            cout << "input first conditions:";
        } else {
            cout << "input second condition:";
        }
        // 次の入力タイプ
        NextInputType inputType = SOME_OR_ALL_OR_NO;
        // 何人目か
        int personCount = 0;
        // 終了フラグ
        bool finFlg = false;
        while (!finFlg) {
            string tmp;
            cin >> tmp;
            if (tmp == "not") {
                pairs[i].notFlg = true;
            } else {
                switch (inputType) {
                    case SOME_OR_ALL_OR_NO:
                        if (tmp == "some") {
                            pairs[i].people1Type = SOME;
                        } else if (tmp == "all") {
                            pairs[i].people1Type = ALL;
                        } else if (tmp == "no") {
                            pairs[i].people1Type = NO;
                        } else {
                            cout << "syntax error" << endl;
                            return false;
                        }
                        inputType = NAME;
                        break;
                    case NAME:
                        pairs[i].peoples[personCount] = tmp;
                        inputType = ARE;
                        if (personCount == 1) {
                            finFlg = true;
                        }
                        break;
                    case ARE:
                        if (tmp != "are") {
                            cout << "syntax error" << endl;
                            return false;
                        }
                        inputType = NAME;
                        personCount++;
                        break;
                }
            }
        }
        if (i == 0) {
            cout << "first condition is loaded." << endl;
        } else {
            cout << "second condition is loaded." << endl;
        }
    }
    return true;
}