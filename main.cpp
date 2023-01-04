#include "iostream"
#include "stack"
#include "cmath"

using namespace std;

const double pi = acos(-1);

double Sin(double d) {
    return (round(sin(d) * 100000000) / 100000000);
}

double Cos(double d) {
    return (round(cos(d) * 100000000) / 100000000);
}

double Ctg(double d) {
    double a = Cos(d);
    double b = Sin(d);
    return (a / b);
}

struct Calc
{
    char type; // тип: 0 для чисел, "+" для операции сложения и тд
    double value; // значение
};

bool Maths(stack <Calc> & Number, stack <Calc> & Operation, Calc & item) {
    double a, b, c;
    a = Number.top().value;
    Number.pop();
    switch (Operation.top().type) {
        case '+':
            b = Number.top().value;
            Number.pop();
            c = a + b;
            item.type = '0';
            item.value = c;
            Number.push(item);
            Operation.pop();
            break;

        case '-':
            b = Number.top().value;
            Number.pop();
            c = b - a;
            item.type = '0';
            item.value = c;
            Number.push(item);
            Operation.pop();
            break;

        case '^':
            b = Number.top().value;
            Number.pop();
            c = pow(b, a);
            item.type = '0';
            item.value = c;
            Number.push(item);
            Operation.pop();
            break;

        case '*':
            b = Number.top().value;
            Number.pop();
            c = a * b;
            item.type = '0';
            item.value = c;
            Number.push(item);
            Operation.pop();
            break;

        case '/':
            b = Number.top().value;
            if (a == 0) {
                cerr << "You can't divide by 0!" << endl;
                return false;
            } else {
                Number.pop();
                c = b / a;
                item.type = '0';
                item.value = c;
                Number.push(item);
                Operation.pop();
                break;
            }
        case 's':
            c = Sin(a);
            item.type = '0';
            item.value = c;
            Number.push(item);
            Operation.pop();
            break;
        case 'c':
            c = Cos(a);
            item.type = '0';
            item.value = c;
            Number.push(item);
            Operation.pop();
            break;
        case 't':
            if (Cos(a) == 0) {
                cerr << "Invalid argument for tg!" << endl;
                return false;
            } else {
                c = tan(a);
                item.type = '0';
                item.value = c;
                Number.push(item);
                Operation.pop();
                break;
            }
        case 'g':
            if (Sin(a) == 0) {
                cerr << "Invalid argument for ctg!" << endl;
                return false;
            } else {
                c = Ctg(a);
                item.type = '0';
                item.value = c;
                Number.push(item);
                Operation.pop();
                break;
            }
        case 'e':
            c = exp(a);
            item.type = '0';
            item.value = c;
            Number.push(item);
            Operation.pop();
            break;

        default:
            cerr << "error";
            return false;
    }
    return true;
}

int get_prior(char st) {
    if (st == 's' || st == 'c' || st == 't' || st == 'g' || st == 'e') return 4;
    if (st == '^') return 3;
    if (st == '+' || st == '-') return 1;
    if (st == '*' || st =='/') return 2;
    else return 0;
}

int main() {
    cout << "Hello!" << endl;
    cout << "To use pi, enter 'p', to use e, enter 'exp(1)'" << endl;
    cout << "Enter an expression: ";
    char st;
    double value;
    bool flag = 1;
    stack<Calc> Number;
    stack<Calc> Operation;
    Calc item;
    while (true) {
        st = cin.peek();
        if (st == '\n') break;
        if (st == ' ') {
            cin.ignore();
            continue;
        }
        if (st == 's' || st == 'c' || st == 'e') {
            char fun[3];
            for (int i = 0; i < 3; i++) {
                st = cin.peek();
                fun[i] = st;
                cin.ignore();
            }
            if (fun[0] == 's' && fun[1] == 'i' && fun[2] == 'n') {
                item.type = 's';
                item.value = 0;
                Operation.push(item);
                continue;
            }
            if (fun[0] == 'c' && fun[1] == 'o' && fun[2] == 's') {
                item.type = 'c';
                item.value = 0;
                Operation.push(item);
                continue;
            }
            if (fun[0] == 'c' && fun[1] == 't' && fun[2] == 'g') {
                item.type = 'g';
                item.value = 0;
                Operation.push(item);
                continue;
            }
            if (fun[0] == 'e' && fun[1] == 'x' && fun[2] == 'p') {
                item.type = 'e';
                item.value = 0;
                Operation.push(item);
                continue;
            }
        }
        if (st == 't') {
            char fun[2];
            for (int i = 0; i < 2; i++) {
                st = cin.peek();
                fun[i] = st;
                cin.ignore();
            }
            if (fun[0] == 't' && fun[1] == 'g') {
                item.type = 't';
                item.value = 0;
                Operation.push(item);
                continue;
            }
        }
        if (st == 'p') {
            item.type = '0';
            item.value = pi;
            Number.push(item);
            flag = 0;
            cin.ignore();
            continue;
        }
        if ((st >= '0' && st <= '9') || st == '-' && flag == 1) { //если прочитано число
            cin >> value;
            item.type = '0';
            item.value = value;
            Number.push(item);
            flag = 0;
            continue;
        }
        if (st == '+' || st == '-' && flag == 0 || st == '*' || st == '/' || st == '^') { //если прочитана операция
            if (Operation.size() == 0) {
                item.type = st;
                item.value = 0;
                Operation.push(item);
                cin.ignore();
                continue;
            }
            if (Operation.size() != 0 && get_prior(st) > get_prior(Operation.top().type)) {
                item.type = st;
                item.value = 0;
                Operation.push(item);
                cin.ignore();
                continue;
            }
            if (Operation.size() != 0 && get_prior(st) <= get_prior(Operation.top().type)) {
                if (Maths(Number, Operation, item) == false) {
                    system("pause");
                    return 0;
                }
                continue;
            }
        }
        if (st == '(') {
            item.type = st;
            item.value = 0;
            Operation.push(item);
            cin.ignore();
            continue;
        }
        if (st == ')') {
            while (Operation.top().type != '(') {
                if (Maths(Number, Operation, item) == false) {
                    system("pause");
                    return 0;
                } else continue;
            }
            Operation.pop();
            cin.ignore();
            continue;
        } else {
            cout << "Error!" << endl;
            system("pause");
            return 0;
        }
    }
    while (Operation.size() != 0) {
        if (Maths(Number, Operation, item) == false) {
            system("pause");
            return 0;
        } else continue;
    }
    cout << "Answer: " << Number.top().value << endl;
    return 0;
}

