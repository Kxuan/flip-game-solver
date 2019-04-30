#include <bitset>
#include <iostream>
#include <cstring>
#include <vector>
#include <functional>

using namespace std;

class BaseMap
{
public:
    virtual void set_first_line(uint x) = 0;

    virtual bool find_solution() = 0;

    virtual void press(uint x, uint y) = 0;

    virtual void print_solution() = 0;
};

template<uint N>
class Map : public BaseMap
{
public:
    void set_first_line(uint x) override
    {
        m[0][x] = true;
    }

    void press(uint x, uint y) override
    {
        m[y][x] = !m[y][x];

        if (x > 0) {
            m[y][x - 1] = !m[y][x - 1];
        }
        if (y > 0) {
            m[y - 1][x] = !m[y - 1][x];
        }

        if (x + 1 < N) {
            m[y][x + 1] = !m[y][x + 1];
        }
        if (y + 1 < N) {
            m[y + 1][x] = !m[y + 1][x];
        }
    }

    bool find_step()
    {
        for (int y = 1; y < N; ++y) {
            for (int x = 0; x < N; ++x) {
                if (m[y - 1][x]) {
                    solution[y][x] = true;
                    press(x, y);
                }
            }
        }

        for (int x = 0; x < N; ++x) {
            if (m[N - 1][x]) {
                return false;
            }
        }
        return true;
    }

    bool find_solution() override
    {
        bool backup[N][N]{};

        memcpy(backup, m, sizeof(backup));

        for (uint64_t op = 0; op < ((uint64_t) 1 << (uint64_t) N); ++op) {
            memcpy(m, backup, sizeof(backup));
            memset(solution, 0, sizeof(solution));

            int l1_press = op, i = 0;
            while (l1_press > 0) {
                if (l1_press & 1) {
                    solution[0][i] = true;
                    press(i, 0);
                }
                l1_press >>= 1;
                ++i;
            }

            if (find_step()) {
                return true;
            }
        }

        return false;
    }

    void print_header()
    {

        cout << "┏";
        for (int i = 0; i < N; ++i) {
            cout << "━━";
            if (i + 1 < N) {
                cout << "┳";
            }
        }
        cout << "┓" << endl;
    }

    void print_footer()
    {
        cout << "┗";
        for (int i = 0; i < N; ++i) {
            cout << "━━";
            if (i + 1 < N) {
                cout << "┻";
            }
        }
        cout << "┛" << endl;
    }

    void print_line(const bool line[N])
    {
        cout << "┃";
        for (int i = 0; i < N; ++i) {
            if (line[i]) {
                cout << "〇┃";
            } else {
                cout << "　┃";
            }
        }
        cout << endl;
    }

    void print_frame_line()
    {
        cout << "┣";
        for (int i = 0; i < N; ++i) {
            cout << "━━";
            if (i + 1 < N) {
                cout << "╋";
            }
        }
        cout << "┫" << endl;
    }

    void print_solution() override
    {
        print_header();
        for (int i = 0; i < N; ++i) {
            print_line(solution[i]);
            if (i + 1 < N) {
                print_frame_line();
            }
        }
        print_footer();
    }

private:
    bool solution[N][N];
    bool m[N][N]{};
};

int main(int argc, const char *argv[])
{
    BaseMap *solvers[] = {
            nullptr, nullptr, nullptr, new Map<3>(), new Map<4>(), new Map<5>(),
            new Map<6>(), new Map<7>(), new Map<8>(), new Map<9>(), new Map<10>(),
            new Map<11>(), new Map<12>(), new Map<13>(), new Map<14>(), new Map<15>(),
            new Map<16>(), new Map<17>(), new Map<18>(), new Map<19>(), new Map<20>(),
            new Map<21>(), new Map<22>(), new Map<23>(), new Map<24>(), new Map<25>(),
            new Map<26>(), new Map<27>(), new Map<28>(), new Map<29>(), new Map<30>(),
            new Map<31>(), new Map<32>(), new Map<33>(), new Map<34>(), new Map<35>(),
            new Map<36>(), new Map<37>(), new Map<38>(), new Map<39>(), new Map<40>(),
            new Map<41>(), new Map<42>(), new Map<43>(), new Map<44>(), new Map<45>(),
            new Map<46>(), new Map<47>(), new Map<48>(), new Map<49>(), new Map<50>(),
            new Map<51>(), new Map<52>(), new Map<53>(), new Map<54>(), new Map<55>(),
            new Map<56>(), new Map<57>(), new Map<58>(), new Map<59>(), new Map<60>(),
            new Map<61>(), new Map<62>(), new Map<63>()

    };

    if (argc >= sizeof(solvers) / sizeof(*solvers)) {
        cerr << "too large" << endl;
        return 1;
    }
    BaseMap *m = solvers[argc-1];
    if (m == nullptr) {
        cerr << "invalid map size" << endl;
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '1') {
            m->set_first_line(i - 1);
        }
    }

    if (m->find_solution()) {
        m->print_solution();
    } else {
        cout << "Failed" << endl;
    }
    return 0;
}
