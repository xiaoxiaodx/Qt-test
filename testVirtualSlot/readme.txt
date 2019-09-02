
测试：槽函数为虚函数时，信号槽的连接过程




	有如下这种情况：
		定义一个基类B，有虚槽函数：void slot_virtualFun();
		定义B的子类C，重新实现父类的虚槽函数 void slot_virtualFun();
		
		假如在 另外一个类OtherClass中什么了一个信号void signal_fun(),
		并且 在Other中实现了代码：
			B *b = new C;
			并且将 signal_fun 与B的slot_virtualFun相连，
			那么如果出发了signal_fun信号，将会调用 子类C 的slot_virtualFun，而不是基类B 的 slot_virtualFun
			
		
结论：其实就是类的多态，子类有的先调用子类，槽函数也是一样