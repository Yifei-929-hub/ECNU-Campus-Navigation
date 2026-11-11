#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;

#define MAXVEX  13
#define NUMBER  19
#define INF 999999

typedef string VertexName;            //顶点名称
typedef char replace;                 //顶点代号
typedef string info;                  //顶点信息（简介）
typedef struct {
	VertexName name; //名称
	replace othername; //代号
	info inform; //简介
}Vexs;

typedef int EdgeType;
typedef struct {
	Vexs vexs[MAXVEX];            //顶点表(以中文信息存储)结构体数组
	EdgeType   arc[MAXVEX][MAXVEX];         //邻接矩阵，可看作边
	int vertexesnum, edgesnum;      //图中当前的顶点数和边数
}Graph;



//存储地图信息
//地点名称
VertexName vexname[13] = {
	"东门",
	"河东食堂",
	"文科大楼",
	"北门",
	"田家炳教育书院",
	"共青场",
	"毛主席像",
	"计算机楼",
	"丽娃食堂",
	"理科大楼",
	"河西食堂",
	"菜鸟驿站",
	"西南2门"

};
//地点代号
replace vexothername[13] = {
	'A','B','C','D','E','F','G','H','I','J','K','L','M'
};
//地点简介
info vexinform[13] = {
	"正大门，位于中山北路上",
	"3层楼，面积较小，饭点人多",
	"教育相关专业大本营",
	"金沙江路门，在金沙江路上",
	"集中上课教学楼之一，高层是实验室",
	"大操场，打卡唯一官方指定场地",
	"华东师范大学的毛泽东主席雕像",
	"以机房和实验室为主，为学生提供上机环境和实验条件",
	"面积较小，但拥有独立西餐厅",
	"理科专业的总部大楼，也可上课",
	"三层楼，面积比河东略大，味道更佳",
	"学生快递的取件点，也可进行物品邮寄",
	"枣阳路门，通向枣阳路"

};


//边的起点
string startvex[19] = {
	"东门",
	"东门",
	"河东食堂",
	"河东食堂",
	"文科大楼",
	"文科大楼",
	"田家炳教育书院",
	"田家炳教育书院",
	"北门",
	"共青场",
	"共青场",
	"共青场",
	"计算机楼",
	"计算机楼",
	"毛主席像",
	"理科大楼",
	"菜鸟驿站",
	"菜鸟驿站",
	"西南2门",
};
//边的终点
string endvex[19] = {
	"河东食堂",
	"文科大楼",
	"文科大楼",
	"田家炳教育书院",
	"共青场",
	"计算机楼",
	"北门",
	"共青场",
	"河西食堂",
	"河西食堂",
	"毛主席像",
	"理科大楼",
	"毛主席像",
	"丽娃食堂",
	"理科大楼",
	"西南2门",
	"西南2门",
	"河西食堂",
	"河西食堂",
};
//边的长度
int lengthofroad[19] = {
	200,200,250,300,500,
	400,100,400,350,300,
	200,150,100,200,100,
	350,100,50,100
};

//定位顶点所在位置
int locates(Graph* g, string othername) {
	int i = 0;
	for (i = 0; i < g->vertexesnum; i++) {
		if (g->vexs[i].name == othername) {
			break;
		}
	}
	if (i >= g->vertexesnum) {
		return -1;
	}
	return i;
}


void createGraph(Graph* g) {

	int i, j, k, weight;
	g->vertexesnum = MAXVEX;
	g->edgesnum = NUMBER;

    //存储信息
	for (i = 0; i < g->vertexesnum; i++) {
		g->vexs[i].name = vexname[i];
		g->vexs[i].othername = vexothername[i];
		g->vexs[i].inform = vexinform[i];
	}

	//每条边初始值设为无穷大（999999）
	for (i = 0; i < g->vertexesnum; i++) {
		for (j = 0; j < g->vertexesnum; j++) {
			g->arc[i][j] = INF;
		}
	}
	cout << endl;

	for (k = 0; k < g->edgesnum; k++) {
		string p, q;
		p = startvex[k];
		q = endvex[k];
		weight = lengthofroad[k];
		int m = -1;
		int n = -1;
		m = locates(g, p);
		n = locates(g, q);
		//m，n都为-1，说明没有这个点的信息
		if (m == -1 || n == -1) {
			cout << "there is no vertex." << endl;
			return;
		}
		//给边赋权值
		g->arc[m][n] = weight;
		g->arc[n][m] = weight;
	}
}

//打印所有地点的基本信息
void printGraph(Graph g) {
	int i;
	for (i = 0; i < g.vertexesnum; i++) {
		cout << "地点名称:" << g.vexs[i].name << endl;
		cout << "代号:" << g.vexs[i].othername << endl;
		cout << "简介:" << g.vexs[i].inform << endl;
		cout << "---------------------------------------------------------" << endl;
	}
}

//打印任一地点的基本信息
void find(Graph g, string othername) {
	int i;
	for (i = 0; i < g.vertexesnum; i++) {
		if (othername == g.vexs[i].name) {
			cout << "地点名称:" << g.vexs[i].name << endl;
			cout << "代号:" << g.vexs[i].othername << endl;
			cout << "简介:" << g.vexs[i].inform << endl;
			cout << "-----------------------------------------------------"<<endl;
		}
	}
}

//菜单栏
void menum() {
	cout << "*****！欢迎来到华东师范大学校园地图查询系统！*****" << endl;
	cout << "************  请选择您想进行的操作：  ************" << endl;
	cout << "*******  1、查询华东师范大学所有地点信息  ********" << endl;
	cout << "****  2、查询华东师范大学任一地点的基本信息  *****" << endl;
	cout << "*******  3、查询两个地点间的最短路径和长度  ******" << endl;
	cout << "*****************  4、退出系统  ******************" << endl;
}

//输出任一两点间的最短路径与长度
void Dispath(int dist[], int path[], int start, int end, Graph g)
{
	int i, j, k;
	int  d;
	string apath[MAXVEX];
	for (i = 0; i < g.vertexesnum; i++)
	{
		if (i == end) {
			cout << "从" << g.vexs[start].name << "到" << g.vexs[end].name << "的路径长度为:" << dist[i] << "\t路径为：";


			d = 0; apath[d] = g.vexs[i].name;
			k = path[i];
			if (start == end)
				cout << g.vexs[start].name << "\n";
			else if (k == -1)

				cout << "无路径\n";

			else
			{
				while (k != start)
				{
					d++; apath[d] = g.vexs[k].name;
					k = path[k];
				}
				d++; apath[d] = g.vexs[start].name;

				cout << apath[d];
				for (j = d - 1; j >= 0; j--)
				{
					cout << "->" << apath[j];
				}

			}
		}
	}
}
//求任一两地点之间的最短路径和长度
void shortestPath(Graph g, int s, int e)

{
	int start = s;
	int end = e;
	int length[MAXVEX], pre[MAXVEX];
	int T[MAXVEX];
	int mindis, i, j, u = s;
	for (i = 0; i < g.vertexesnum; i++)
	{
		length[i] = g.arc[s][i];
		T[i] = 0;
		if (g.arc[s][i] < INF)
			pre[i] = s;
		else
			pre[i] = -1;
	}
	length[s] = 0;
	T[s] = 1;
	for (i = 0; i < g.vertexesnum; i++)	 	//循环
	{
		mindis = INF;
		for (j = 0; j < g.vertexesnum; j++)
			if (T[j] == 0 && length[j] < mindis)
			{
				u = j;
				mindis = length[j];
			}

		T[u] = 1;				//加入顶点u
		for (j = 0; j < g.vertexesnum; j++)		//修改距离
			if (T[j] == 0)
				if (length[u] + g.arc[u][j] < length[j])
				{
					length[j] = length[u] + g.arc[u][j];
					pre[j] = u;
				}
	}
	Dispath(length, pre, start, end, g);		//输出最短路径
	cout << endl;
}

//封装上述函数，包含所有功能
int function() {
	Graph g;
	Graph* ptr = &g;
	createGraph(ptr);
	int  s, e;
	char chose;
	string str, start, end;
	while (true) {
		menum();
		cout << endl;
		cout << "请输入操作编号：" << endl;
		cin >> chose;
		switch (chose) {
		case '1':
			printGraph(g);
			break;
		case '2':
			cout << endl;
			cout << "请输入查询地点的名称:";
			cin >> str;
			if (locates(ptr, str) == -1) {
				cout << "----------------查询地点不存在,请重新操作------------------" << endl;
				break;
			}
			else {
				find(g, str);
			}
			break;
		case '3':
			cout << "请输入任意两地的名称（名称之间用空格隔开，以回车结束）：" << endl;
			cin >> start >> end;
			s = locates(ptr, start);
			e = locates(ptr, end);
			if (s == -1 || e == -1) {
				cout << "----------------查询地点不存在,请重新操作------------------" << endl;
				break;
			}
			else {
				shortestPath(g, s, e);
			}
			cout << endl;
			break;
		case '4':
			cout << "-----------------感谢，欢迎下次使用！-------------------" << endl;
			return 0;
		default:
			cout << "----------------操作数输入错误，请重新操作！------------------" << endl;
			break;
		}
		cin.ignore(100, '\n');
	}
}
int main(int argc, char** argv) {
	function();
	system("pause");
	return 0;
}
