#include <array>
#include <functional>
#include <limits>
#include <vector>

template <std::size_t memSize = 1000000>
class IntCodeInterpreter {
   public:
    IntCodeInterpreter(const std::vector<long long>& programm,
                       std::function<long long(long long)> input,
                       std::function<void(long long)> output,
                       bool printErrorMsgs)
        : programm(memSize, 0),
          input(input),
          output(output),
          printErrorMsgs(printErrorMsgs) {
        this->programm.assign(programm.begin(), programm.end());
    }
    IntCodeInterpreter(const std::vector<long long>& programm,
                       std::function<long long(long long)> input,
                       std::function<void(long long)> output)
        : programm(memSize, 0),
          input(input),
          output(output),
          printErrorMsgs(true) {
        this->programm.assign(programm.begin(), programm.end());
    }
    IntCodeInterpreter(const IntCodeInterpreter&) = default;
    IntCodeInterpreter& operator=(const IntCodeInterpreter&) = default;

    IntCodeInterpreter(IntCodeInterpreter&&) = delete;
    IntCodeInterpreter& operator=(IntCodeInterpreter&&) = delete;
    ~IntCodeInterpreter() = default;

    void memdump(int size) {
        for (int i = 0; i < size; ++i) printf("%lld, ", programm[i]);
        printf("\n");
    }

    void run() {
        while (eval())
            ;
    }

    void reset(const std::vector<long long>& programm) {
        pc = relativeBase = inputCount = 0;
        std::fill(this->programm.begin(), this->programm.end(), 0);
        this->programm.assign(programm.begin(), programm.end());
    }

    long long& modifyMemory(int index) { return programm[index]; }

    bool eval() {
        // get opcode and parameter codes
        int op = programm[pc] % 100;
        for (int i = 0, t = programm[pc] / 100; i < 3; ++i, t /= 10)
            params[i] = t % 10;

        switch (op) {
            case 1:
                write(3) = getArg(1) + getArg(2);
                pc += 4;
                break;
            case 2:
                write(3) = getArg(1) * getArg(2);
                pc += 4;
                break;
            case 3: {
                long long result = input(inputCount++);
                if (result == std::numeric_limits<long long>::min()) {
                    if (printErrorMsgs) printf("ERROR: input interupt!\n");
                    return false;
                }
                write(1) = result;
                pc += 2;
                break;
            }
            case 4:
                output(getArg(1));
                pc += 2;
                break;
            case 5:
                if (getArg(1))
                    pc = getArg(2);
                else
                    pc += 3;
                break;
            case 6:
                if (!getArg(1))
                    pc = getArg(2);
                else
                    pc += 3;
                break;
            case 7:
                write(3) = getArg(1) < getArg(2) ? 1 : 0;
                pc += 4;
                break;
            case 8:
                write(3) = getArg(1) == getArg(2) ? 1 : 0;
                pc += 4;
                break;
            case 9:
                relativeBase += getArg(1);
                pc += 2;
                break;
            case 99:
                if (printErrorMsgs) printf("HALT!\n");
                return false;
            default:
                if (printErrorMsgs)
                    printf("ERROR: op code %d not valid!\n", op);
                return false;
        }
        return true;
    }

   private:
    std::vector<long long> programm;
    int pc = 0;
    int relativeBase = 0;

    long long inputCount = 0;

    bool printErrorMsgs;

    std::function<long long(long long)> input;
    std::function<void(long long)> output;

    std::array<int, 3> params;

    long long getArg(int numArg) {
        int param = params[numArg - 1];
        int add = pc + numArg;
        switch (param) {
            case 0:
                return programm[programm[add]];
            case 1:
                return programm[add];
            case 2:
                return programm[relativeBase + programm[add]];
            default:
                printf("unknown parameter mode %d!\n", param);
                return 0;
        }
    }

    long long& write(int numArg) {
        int param = params[numArg - 1];
        int add = pc + numArg;
        switch (param) {
            case 0:
                return programm[programm[add]];
            case 2:
                return programm[relativeBase + programm[add]];
            default:
                printf("invalid param mode %d!\n", param);
                return programm[0];
        }
    }
};
