#include <csignal>
#include <iostream>
#include <cstdlib>

class Tester {
public:
	Tester() { std::cout << "Tester ctor\n"; }
	~Tester() { std::cout << "Tester dtor\n"; }
};

Tester static_tester; 

void signal_handler(int signal)
{
	if (signal == SIGABRT) {//abort()信号
		std::cerr << "abort error\n";//Cerr通常用于输出错误信息与其他不属于正常逻辑的输出内容。
	}
	else {
		std::cerr << "Unexpected signal " << signal << " received\n";
	}
	std::_Exit(EXIT_FAILURE);
}

int main()
{
	Tester automatic_tester; // Destructor not called

	auto previous_handler = std::signal(SIGABRT, signal_handler);//绑定了一个信号，如果出现abort，就调用函数signal_handler
	if (previous_handler == SIG_ERR) {
		std::cerr << "Setup failed\n";
		return EXIT_FAILURE;
	}

	std::abort();  // 触发 SIGABRT
	std::cout << "This code is unreachable\n";
}