#include <bits/stdc++.h>
#include <vector>
#include <unordered_map>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'journeyToMoon' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY astronaut
 */

vector<long> representatives;

long findRep(long idx) {
    if (representatives[idx] == idx) return idx;
    else {
        long tmp = findRep(representatives[idx]);
        representatives[idx] = tmp;
        return tmp;
    }
}

void printRepresentatives() {
    for(int astIdx = 0; astIdx < representatives.size(); ++astIdx) {
        cout << astIdx << " isRepresentedBy " << representatives[astIdx] << endl;
    }
    cout << "--------" << endl;
}

long journeyToMoon(long n, vector<vector<long>> astronaut) {
    representatives.clear();
    representatives.reserve(n);

    for (long idx = 0; idx < n; ++idx) {
        representatives.push_back(idx);
    }

    for (long idx = 0; idx < astronaut.size(); ++idx) {
        long firstAstronautIdx = astronaut[idx][0];
        long secondAstronautIdx = astronaut[idx][1];

        long firstRepresentative = findRep(firstAstronautIdx);
        long secondRepresentative = findRep(secondAstronautIdx);

        representatives[firstRepresentative] = secondRepresentative;
    };

    for (long astIdx = 0; astIdx < n; ++astIdx) {
         representatives[astIdx] = findRep(astIdx);
    }

    unordered_map<long, long> countMap;
    for(long astIdx = 0; astIdx < n; ++astIdx) {
        countMap[representatives[astIdx]]++;
    }

    long result = 0;
    long included = 0;

    for (auto& it: countMap) {
        result += included * it.second;
        included += it.second;
    }
    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    long n = stoi(first_multiple_input[0]);

    long p = stoi(first_multiple_input[1]);

    vector<vector<long>> astronaut(p);

    for (long i = 0; i < p; i++) {
        astronaut[i].resize(2);

        string astronaut_row_temp_temp;
        getline(cin, astronaut_row_temp_temp);

        vector<string> astronaut_row_temp = split(rtrim(astronaut_row_temp_temp));

        for (long j = 0; j < 2; j++) {
            long astronaut_row_item = stoi(astronaut_row_temp[j]);

            astronaut[i][j] = astronaut_row_item;
        }
    }

    long result = journeyToMoon(n, astronaut);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
