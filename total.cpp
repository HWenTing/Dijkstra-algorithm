#include<iostream>
#include<string>
using namespace std;

//记录起点到每个顶点的最短路径的信息
struct Dis {
	string path;
	int value;
	bool visit;
	Dis() {
		visit = false; //对应已经找到的最短路径的集合
		value = 0; //最终路径长度
		path = ""; //记录路径信息
	}
};

//邻接链表Node节点
struct Node {
	int element;
	int value;
	Node *next;
	Node() {}
	Node(int element, int value) {
		this->element = element;
		this->value = value;
	}
};

/*

图的存储结构为邻接链表时所对应的Graph_AL类

*/

class Graph_AL {
private:
	int vexnum;//图的顶点个数
	int edge;//图的边数
	Node *aList;//邻接链表
	Dis *dis;//记录各个顶点最短路径的信息
public:
	//构造函数
	Graph_AL(int vexnum, int edge);
	//析构函数
	~Graph_AL();
	// 边的合法性检测 ; 顶点从1开始编号
	bool check_edge_value(int start, int end, int weight);
	//创建图
	void createGraph();
	//打印邻接链表
	void print();
	//求最短路径
	void Dijkstra(int begin);
	//打印最短路径
	void print_path(int);
};

//构造函数
Graph_AL::Graph_AL(int vexnum, int edge) {
	//初始化顶点和边
	this->vexnum = vexnum;
	this->edge = edge;
	//为邻接表开辟空间
	aList = new Node[this->vexnum];
	dis = new Dis[this->vexnum];
	//初始化
	for (int i = 0;i < this->vexnum;i++) {
		aList[i].element = i;
		aList[i].next = NULL;
	}

}

//析构函数
Graph_AL::~Graph_AL() {
	//释放空间
	delete[] dis;
	delete[] aList;
}

// 边的合法性检测 ; 顶点从1开始编号
bool Graph_AL::check_edge_value(int start, int end, int weight) {
	if (start<1 || end<1 || start>vexnum || end>vexnum || weight < 0) {
		return false;
	}
	return true;
}

//创建图
void Graph_AL::createGraph() {
	cout << "请输入每条边的起点和终点（顶点编号从1开始）以及其权重" << endl;
	int start;
	int end;
	int weight;
	int count = 0;
	while (count != this->edge) {
		cin >> start >> end >> weight;
		//首先判断边的信息是否合法
		while (!this->check_edge_value(start, end, weight)) {
			cout << "输入的边的信息不合法，请重新输入" << endl;
			cin >> start >> end >> weight;
		}
		//在邻接链表中添加
		Node *current2 = aList[start - 1].next;

		aList[start - 1].next = new Node(end, weight);
		aList[start - 1].next->next = current2;
		count++;

	}
}

//打印邻接链表
void Graph_AL::print() {
	cout << "图的邻接链表为：" << endl;
	for (int i = 0;i < this->vexnum;i++) {
		Node *current1 = aList[i].next;
		cout << i + 1;
		while (current1 != NULL) {
			cout << "--->" << current1->element;
			current1 = current1->next;
		}
		cout << endl;
	}
}

//求最短路径
void Graph_AL::Dijkstra(int begin) {
	Node current = aList[begin - 1];

	//初始化Dis
	for (int i = 0;i < this->vexnum;i++) {
		dis[i].value = INT_MAX;
	}
	dis[begin - 1].path = "v" + to_string(begin) + "-->v" + to_string(begin);

	while (current.next != NULL) {
		//设置当前的路径
		current = *current.next;
		dis[current.element - 1].path = "v" + to_string(begin) + "-->v" + to_string(current.element);
		dis[current.element - 1].value = current.value;
	}

	//设置起点的到起点的路径为0
	dis[begin - 1].value = 0;
	dis[begin - 1].visit = true;

	int count = 1;
	//计算剩余的顶点的最短路径（剩余this->vexnum-1个顶点）
	while (count != this->vexnum) {
		//temp用于保存当前dis数组中最小的那个下标
		//min记录的当前的最小值
		int temp = 0;
		int min = INT_MAX;
		for (int i = 0; i < this->vexnum; i++) {
			if (!dis[i].visit && dis[i].value<min) {
				min = dis[i].value;
				temp = i;
			}
		}
		//把temp对应的顶点加入到已经找到的最短路径的集合中
		dis[temp].visit = true;
		++count;

		for (int i = 0; i < this->vexnum; i++) {
			if (!dis[i].visit) {
				Node icurrent = aList[temp];
				while (icurrent.next != NULL) {
					icurrent = *icurrent.next;
					if (icurrent.element == i + 1 && (dis[temp].value + icurrent.value) < dis[i].value) {
						//如果新得到的边可以影响其他为访问的顶点，那就就更新它的最短路径和长度
						dis[i].value = dis[temp].value + icurrent.value;
						dis[i].path = dis[temp].path + "-->v" + to_string(i + 1);
					}
				}
			}
		}
	}
}

//打印最短路径
void Graph_AL::print_path(int begin) {
	string str;
	str = "v" + to_string(begin);
	cout << "以" << str << "为起点的图的最短路径为：" << endl;
	for (int i = 0; i != this->vexnum; i++) {
		if (dis[i].value != INT_MAX)
			cout << dis[i].path << "=" << dis[i].value << endl;
		else {
			cout << "v" + to_string(begin) + "-->v" + to_string(i + 1) << "是无最短路径的" << endl;
		}
	}
}




/*

图的存储结构为邻接矩阵时所对应的Graph_DG类

*/



class Graph_DG {
private:
	int vexnum;   //图的顶点个数
	int edge;     //图的边数
	int **arc;   //邻接矩阵
	Dis * dis;   //记录各个顶点最短路径的信息

public:
	//构造函数
	Graph_DG(int vexnum, int edge);
	//析构函数
	~Graph_DG();
	// 边的合法性检测 ; 顶点从1开始编号
	bool check_edge_value(int start, int end, int weight);
	//创建图
	void createGraph();
	//打印邻接矩阵
	void print();
	//求最短路径
	void Dijkstra(int begin);
	//打印最短路径
	void print_path(int);
};

//构造函数
Graph_DG::Graph_DG(int vexnum, int edge) {
	//初始化顶点数和边数
	this->vexnum = vexnum;
	this->edge = edge;
	//为邻接矩阵开辟空间和赋初值
	arc = new int*[this->vexnum];
	dis = new Dis[this->vexnum];
	for (int i = 0; i < this->vexnum; i++) {
		arc[i] = new int[this->vexnum];
		for (int k = 0; k < this->vexnum; k++) {
			//邻接矩阵初始化为无穷大
			arc[i][k] = INT_MAX;
		}
	}
}

//析构函数
Graph_DG::~Graph_DG() {
	delete[] dis;
	for (int i = 0; i < this->vexnum; i++) {
		delete this->arc[i];
	}
	delete arc;
}

// 边的合法性检测; 顶点从1开始编号
bool Graph_DG::check_edge_value(int start, int end, int weight) {
	if (start<1 || end<1 || start>vexnum || end>vexnum || weight < 0) {
		return false;
	}
	return true;
}

//创建图
void Graph_DG::createGraph() {
	cout << "请输入每条边的起点和终点（顶点编号从1开始）以及其权重" << endl;
	int start;
	int end;
	int weight;
	int count = 0;
	while (count != this->edge) {
		cin >> start >> end >> weight;
		//首先判断边的信息是否合法
		while (!this->check_edge_value(start, end, weight)) {
			cout << "输入的边的信息不合法，请重新输入" << endl;
			cin >> start >> end >> weight;
		}
		//对邻接矩阵对应上的点赋值
		arc[start - 1][end - 1] = weight;
		//对边计数
		++count;
	}
}

//打印邻接矩阵
void Graph_DG::print() {
	cout << "图的邻接矩阵为：" << endl;
	int count_row = 0; //打印行的标签
	int count_col = 0; //打印列的标签
					   //开始打印
	while (count_row != this->vexnum) {
		count_col = 0;
		while (count_col != this->vexnum) {
			if (arc[count_row][count_col] == INT_MAX)//不存在边
				cout << "∞" << " ";
			else //存在对应的边
				cout << arc[count_row][count_col] << " ";
			++count_col;
		}
		cout << endl;
		++count_row;
	}
}

//求最短路径
void Graph_DG::Dijkstra(int begin) {
	//初始化dis数组
	int i;
	for (i = 0; i < this->vexnum; i++) {
		//设置当前的路径
		dis[i].path = "v" + to_string(begin) + "-->v" + to_string(i + 1);
		dis[i].value = arc[begin - 1][i];
	}
	//设置起点的到起点的路径为0
	dis[begin - 1].value = 0;
	dis[begin - 1].visit = true;

	int count = 1;
	//计算剩余的顶点的最短路径（剩余this->vexnum-1个顶点）
	while (count != this->vexnum) {
		//temp用于保存当前dis数组中最小的那个下标
		//min记录的当前的最小值
		int temp = 0;
		int min = INT_MAX;
		for (i = 0; i < this->vexnum; i++) {
			if (!dis[i].visit && dis[i].value<min) {
				min = dis[i].value;
				temp = i;
			}
		}
		
		//把temp对应的顶点加入到已经找到的最短路径的集合中
		dis[temp].visit = true;
		++count;
		for (i = 0; i < this->vexnum; i++) {
			//更新源点到其他点的距离信息
			if (!dis[i].visit && arc[temp][i] != INT_MAX && (dis[temp].value + arc[temp][i]) < dis[i].value) {
				//如果新得到的边可以影响其他为访问的顶点，那就就更新它的最短路径和长度
				dis[i].value = dis[temp].value + arc[temp][i];
				dis[i].path = dis[temp].path + "-->v" + to_string(i + 1);
			}
		}
	}
}

//打印最短路径
void Graph_DG::print_path(int begin) {
	string str;
	str = "v" + to_string(begin);
	cout << "以" << str << "为起点的图的最短路径为：" << endl;
	for (int i = 0; i != this->vexnum; i++) {
		if (dis[i].value != INT_MAX && dis[i].value >= 0)
			cout << dis[i].path << "=" << dis[i].value << endl;
		else {
			cout << "v" + to_string(begin) + "-->v" + to_string(i + 1) << "是无最短路径的" << endl;
		}
	}
}



/*

图的存储结构为边集数组时所对应的Graph_EA类

*/


struct Edge {
	int begin;//记录起点
	int end;//记录尾点
	int weight;//记录权重
	Edge() {
		begin = 0;
		end = 0;
		weight = 0;
	}
};
/*
存储结构为边集数组
*/

class Graph_EA {
private:
	int vexnum;   //图的顶点个数
	int edge;     //图的边数
	Edge * edges;   //邻接矩阵
	Dis * dis;   //记录各个顶点最短路径的信息
public:
	//构造函数
	Graph_EA(int vexnum, int edge);
	//析构函数
	~Graph_EA();
	// 判断我们每次输入的的边的信息是否合法
	//顶点从1开始编号
	bool check_edge_value(int start, int end, int weight);
	//创建图
	void createGraph();
	//打印邻接矩阵
	void print();
	//求最短路径
	void Dijkstra(int begin);
	//打印最短路径
	void print_path(int);
};


//构造函数
Graph_EA::Graph_EA(int vexnum, int edge) {
	//初始化顶点数和边数
	this->vexnum = vexnum;
	this->edge = edge;
	//为邻接矩阵开辟空间和赋初值
	edges = new Edge[this->edge];
	dis = new Dis[this->vexnum];
	
}

//析构函数
Graph_EA::~Graph_EA() {
	delete[] dis;
	
	delete []edges;
}



// 边的合法性检测; 顶点从1开始编号
bool Graph_EA::check_edge_value(int start, int end, int weight) {
	if (start<1 || end<1 || start>vexnum || end>vexnum || weight < 0) {
		return false;
	}
	return true;
}


//创建图
void Graph_EA::createGraph() {
	cout << "请输入每条边的起点和终点（顶点编号从1开始）以及其权重" << endl;
	int start;//起点
	int end;//尾点
	int weight;//权重
	int count = 0;
	while (count != this->edge) {
		cin >> start >> end >> weight;
		//首先判断边的信息是否合法
		while (!this->check_edge_value(start, end, weight)) {
			cout << "输入的边的信息不合法，请重新输入" << endl;
			cin >> start >> end >> weight;
		}
		edges[count].begin = start;
		edges[count].end = end;
		edges[count].weight = weight;
		++count;
	}
}


//打印边集数组
void Graph_EA::print() {
	cout << "图的边集数组为：" << endl;
	cout << "边组数	      begin     end    weight" << endl;
	for (int i = 0;i < this->edge;i++) {
		cout << "edges[" + to_string(i) + "]	" << to_string(edges[i].begin) + "	" 
			<< to_string(edges[i].end) + "	" << to_string(edges[i].weight) << endl;
	}

}


//求最短路径
void Graph_EA::Dijkstra(int begin) {
	//首先初始化我们的dis数组
	int i;
	for (i = 0; i < this->vexnum; i++) {
		//设置当前的路径
		dis[i].path = "v" + to_string(begin) + "-->v" + to_string(i + 1);
		dis[i].value = INT_MAX;
	}
	for (i = 0;i < this->edge;i++) {
		if (edges[i].begin == begin) {
			dis[edges[i].end-1].value = edges[i].weight;
		}
	}


	//设置起点的到起点的路径为0
	dis[begin - 1].value = 0;
	dis[begin - 1].visit = true;

	int count = 1;
	//计算剩余的顶点的最短路径（剩余this->vexnum-1个顶点）

	while (count != this->vexnum) {
		//temp用于保存当前dis数组中最小的那个下标
		//min记录的当前的最小值
		int temp = 0;
		int min = INT_MAX;
		for (i = 0; i < this->vexnum; i++) {
			if (!dis[i].visit && dis[i].value<min) {
				min = dis[i].value;
				temp = i;
			}
		}
		
		//把temp对应的顶点加入到已经找到的最短路径的集合中
		dis[temp].visit = true;
		++count;
		for (int j = 0;j < this->edge;j++) {
			if (edges[j].begin-1 == temp) {//判断是否要更新
				if (!dis[edges[j].end-1].visit && (dis[temp].value + edges[j].weight) < dis[edges[j].end-1].value) {
					//如果新得到的边可以影响其他为访问的顶点，那就就更新它的最短路径和长度
					dis[edges[j].end-1].value = dis[temp].value + edges[j].weight;
					dis[edges[j].end-1].path = dis[temp].path + "-->v" + to_string(edges[j].end);
				}
			}
		}
	}
	
}


//打印最短路径
void Graph_EA::print_path(int begin) {
	string str;
	str = "v" + to_string(begin);
	cout << "以" << str << "为起点的图的最短路径为：" << endl;
	for (int i = 0; i != this->vexnum; i++) {
		if (dis[i].value != INT_MAX && dis[i].value >= 0)
			cout << dis[i].path << "=" << dis[i].value << endl;
		else {
			cout << "v" + to_string(begin) + "-->v" + to_string(i + 1) << "是无最短路径的" << endl;
		}
	}
}



//检测输入顶点和边的信息
bool check(int Vexnum, int edge) {
	if (Vexnum <= 0 || edge <= 0 || ((Vexnum*(Vexnum - 1)) / 2) < edge)
		return false;
	return true;
}



//main方法
int main() {
	int vexnum; 
	int edge;
	int choice; 
	int source;
	char q;
	cout << "Dijkstra算法求解出单源点到其他各顶点的最短路径" << endl;
	//持续获得用户输入
	do {
		//获取图的顶点和边数
		cout << "输入图的顶点个数和边的条数：" << endl;
		cin >> vexnum >> edge;

		//检测输入的顶点和边的信息
		while (!check(vexnum, edge)) {
			cout << "输入的数值不合法，请重新输入" << endl;
			cin >> vexnum >> edge;
		}

		//获取源点
		cout << "输入源点：" << endl;
		cin >> source;

		//用户选择图的存储结构
		cout << "请输入1 - 3数字，其1代表图的存储结构为邻接矩阵，2代表图的存储结构为邻接链表，3代表图的存储结构为边集数组" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1: {
			//邻接矩阵
			Graph_DG graph(vexnum, edge);
			graph.createGraph();
			graph.print();
			graph.Dijkstra(source);
			graph.print_path(source);
			break;}
		case 2: {
			//邻接链表
			Graph_AL graph(vexnum, edge);
			graph.createGraph();
			graph.print();
			graph.Dijkstra(source);
			graph.print_path(source);
			break;}
		case 3: {
			//邻接链表
			Graph_EA graph(vexnum, edge);
			graph.createGraph();
			graph.print();
			graph.Dijkstra(source);
			graph.print_path(source);
			break;}
		default:
			cout << "输入错误" << endl;
			break;
		}
		cout << "若想退出，请按q，否则其他按任意键继续" << endl;
		cin >> q;
	} while (q != 'q');


	system("pause");
	return 0;
}