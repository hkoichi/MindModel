#include <iostream>
#include <vector>

using namespace std;

#define MAX_WORD_NUM 20

enum NextInputType {
    SOME_OR_ALL_OR_NO,
    NAME,
    ARE
};

enum PartnerType {
    ALL,
    SOME,
    NO,
    NO_EXIST
};

class Pair {
public:
    string peoples[2];
    PartnerType types[2] = {SOME, SOME};
    bool notFlg = false;
};

Pair pairs[2];

bool loadConditions();

bool loadCommonPeople();

void makeMentalModel();

string makeGoodSpaces(PartnerType type, string s);

void printMentalModel(vector<vector<PartnerType>> mentalModel);

int main() {
    // 読み込み
    if (!loadConditions()) {
        cout << "syntax error" << endl;
        return -1;
    }
    // 共通の職種をpairs[0]のpeoples[1]、pairs[1]のpeoples[0]にくるようにする
    if (loadCommonPeople()) {
        makeMentalModel();
    } else {
        cout << "there is no common people" << endl;
        return -1;
    }
    return 0;
}


void makeMentalModel() {
    vector<vector<PartnerType >> mentalModel;
    vector<PartnerType> tmp;
    Pair pair1 = pairs[0];
    Pair pair2 = pairs[1];
    if (pair1.types[0] == SOME) {
        if (pair1.types[1] == SOME) {
            tmp = {SOME, NO_EXIST, NO_EXIST};
            mentalModel.push_back(tmp);
            tmp = {SOME, SOME, NO_EXIST};
            mentalModel.push_back(tmp);
            tmp = {NO_EXIST, SOME, NO_EXIST};
            mentalModel.push_back(tmp);
        } else {
            tmp = {SOME, NO_EXIST, NO_EXIST};
            mentalModel.push_back(tmp);
            tmp = {SOME, ALL, NO_EXIST};
            mentalModel.push_back(tmp);
        }
    } else if (pair1.types[0] == ALL) {
        if (!pair1.notFlg) {
            tmp = {ALL, SOME, NO_EXIST};
            mentalModel.push_back(tmp);
        } else {
            tmp = {ALL, NO_EXIST, NO_EXIST};
            mentalModel.push_back(tmp);
            tmp = {NO_EXIST, SOME, NO_EXIST};
            mentalModel.push_back(tmp);
        }
    }


    printMentalModel(mentalModel);
    return;
}

void printMentalModel(vector<vector<PartnerType>> mentalModel) {
    string people[3];
    people[0] = pairs[0].peoples[0];
    people[1] = pairs[0].peoples[1];
    people[2] = pairs[1].peoples[1];
    for (vector<PartnerType> mental : mentalModel) {
        for (int i = 0; i < 3; ++i) {
            cout << makeGoodSpaces(mental[i], people[i]);
            if (i == 0 || i == 1) {
                cout << ":";
            } else {
                cout << endl;
            }
        }
    }
}

string makeGoodSpaces(PartnerType type, string s) {
    string ans = "";
    switch (type) {
        case SOME:
            ans += s;
            for (int i = 0; i < MAX_WORD_NUM - s.size(); ++i) {
                ans += " ";
            }
            break;
        case ALL:
            ans += "[";
            ans += s;
            ans += "]";
            for (int i = 0; i < MAX_WORD_NUM - s.size() - 2; ++i) {
                ans += " ";
            }
            break;
        case NO_EXIST:
            for (int i = 0; i < MAX_WORD_NUM; ++i) {
                ans += " ";
            }
            break;
    }
    return ans;
}

bool loadCommonPeople() {
    bool ans = false;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (pairs[0].peoples[i] == pairs[1].peoples[j]) {
                if (i == 0) {
                    string temp = pairs[0].peoples[0];
                    pairs[0].peoples[0] = pairs[0].peoples[1];
                    pairs[0].peoples[1] = temp;
                    pairs[0].types[1] = pairs[0].types[0];
                    pairs[0].types[0] = SOME;
                }
                if (j == 1) {
                    string temp = pairs[1].peoples[0];
                    pairs[1].peoples[0] = pairs[1].peoples[1];
                    pairs[1].peoples[1] = temp;
                    pairs[1].types[1] = pairs[1].types[0];
                    pairs[1].types[0] = SOME;
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
                            pairs[i].types[0] = SOME;
                        } else if (tmp == "all") {
                            pairs[i].types[0] = ALL;
                        } else if (tmp == "no") {
                            pairs[i].types[0] = NO;
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