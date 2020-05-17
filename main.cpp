#include <iostream>
using std::cout;

// template method
class IWorker {
protected:
    virtual bool action1() = 0;
    virtual bool action2() = 0;
    virtual bool action3() = 0;

public:
    // template method
    bool run() {
        if (action1())
            return action2();
        else
            return action3();
    }
};

class CodeWriter: public IWorker {
private:
    bool tired;
protected:
    virtual bool action1() override {
        cout << "Check if not tired...\n";
        return tired;
    }
    virtual bool action2() override {
        cout << "Need a rest, sorry!\n";
        return false;
    }
    virtual bool action3() override {
        cout << "Writing some code...\n";
        tired = true;
        return true;
    }

public:
    CodeWriter(bool tired = false) : tired(tired) {}

    void relax() {
        cout << "Relaxing...\n";
        tired = false;
    }
};

int main() {
    CodeWriter cw;

    cw.run();
    cw.run();
    cw.relax();
    cw.run();

    return 0;
}
