#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using std::cout;
using std::vector;
using std::string;
using std::stringstream;

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

template <typename T>
class IData {
public:
    virtual ~IData() = default;
    virtual T& get_data() = 0;
    virtual void set_data(T& data_) = 0;
    virtual string to_string() = 0;
};

using VecIntData = IData<vector<int>>;

class DataStorage: public VecIntData {
private:
    static constexpr size_t VEC_SIZE = 10;
    vector<int> data;
public:
    DataStorage() {
        data.reserve(VEC_SIZE);
        for(size_t i=0; i<VEC_SIZE; ++i)
            data.push_back(rand()%100);
    }

    vector<int>& get_data() override { return data; }
    void set_data(vector<int>& data_) override { data = data_; }

    string to_string() override {
        stringstream ss;
        for(auto& item: data)
            ss << item << " ";
        ss << '\n';
        return ss.str();
    }
};

class VecIntDataDecorator : public VecIntData {
protected:
    VecIntData& component;
public:
    explicit VecIntDataDecorator(VecIntData& dt): component(dt) {}

    vector<int>& get_data() override {return component.get_data();}
    void set_data(vector<int>& data_) override {component.set_data(data_);}

    string to_string() override { return component.to_string(); }
};

class AddNumberDecorator: public VecIntDataDecorator {
private:
    int number;
public:
    AddNumberDecorator(VecIntData& dt, int num): VecIntDataDecorator(dt), number(num) {}

    vector<int>& get_data() override {
        auto& data = component.get_data();
        for(auto& item: data)
            item -= number;
        return data;
    }
    void set_data(vector<int>& data_) override {
        for(auto& item: data_)
            item += number;
        component.set_data(data_);
    }
};

class MultiplyNumberDecorator: public VecIntDataDecorator {
    int number;
public:
    MultiplyNumberDecorator(VecIntData& dt, int num): VecIntDataDecorator(dt), number(num) {}

    vector<int>& get_data() override {
        auto& data = component.get_data();
        for(auto& item: data)
            item /= number;
        return data;
    }
    void set_data(vector<int>& data_) override {
        for(auto& item: data_)
            item *= number;
        component.set_data(data_);
    }
};

int main() {
//    CodeWriter cw;
//    cw.run();
//    cw.run();
//    cw.relax();
//    cw.run();

    DataStorage ds1;
    AddNumberDecorator add_two(ds1, 2);
    MultiplyNumberDecorator mul_two(add_two, 2);

    DataStorage ds2;
    cout << ds2.to_string();
    mul_two.set_data(ds2.get_data());
    cout << mul_two.to_string();


    return 0;
}
