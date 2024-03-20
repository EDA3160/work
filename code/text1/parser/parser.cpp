#include"parser.h"
//读取文件中的数据并存入相应的数据结构
void parseDie(std::ifstream& ifs, DieSize& die)//考虑到要存的数据类型为整形，所以一段一段流入字符串，再把字符串中的数字转为整形数据
{
    std::string line;
    while (getline(ifs, line))
    {
        if (line.empty())
            return;
        std::istringstream ss(line);
        std::string num;
        int pos = 0;
        while (ss >> num)
        {
            if (pos == 1)
                die.width = std::stoi(num);
            else if (pos == 2)
                die.heigth = std::stoi(num);
            pos++;
        }
    }
}
void parseInstances(std::ifstream& ifs, NumInstances& instance)//利用寻找字串的方法来定位数据的位置
{
    std::string line;
    std::string title = "NumInstances";
    getline(ifs, line);
    int pos = line.find(title);
    int start = -1;
    for (int i = pos + title.size(); i < line.size(); i++)
    {
        int start = i;
        if (line[i] == ' ')
        {
            if (start == -1)
                continue;
            else
            {
                instance.size = std::stoi(line.substr(start, i));//数据转换
                break;
            }
        }
        else if (line[i] == '#')//无效信息直接结束
            break;
        else
        {
            if (start == -1)
                start = i;
        }
    }
    std::string name = "Inst";
    for(int i = 0; i < instance.size; i++)//找到数据的位置并取字串赋值
    {
        start = -1;
        getline(ifs, line);
        pos = line.find(name);
        for (int j = pos + name.size(); j < line.size(); j++)
        {
            if (line[j] == ' ')
            {
                if (start == -1)
                    continue;
                instance.instances.push_back(line.substr(start, j - start));
            }
            else if (line[j] == '#')
                break;
            else if (j == line.size() - 1 && start != -1)
                instance.instances.push_back(line.substr(start, j));
            else
            {
                if (start == -1)
                    start = j;
            }
        }
    }
    getline(ifs, line);
}
void parseNumNets(std::ifstream& ifs, NumNets& numnets)
{
    std::string line;
    getline(ifs, line);

    std::istringstream ss(line);
    std::string num;
    ss >> num;
    ss >> num;
    numnets.size = std::stoi(num);
}
void parseNets(std::ifstream& ifs, Net& net)//由于txt里面的数据存放位置有一定规则，直接找规律存入数据
{
    std::string line;
    getline(ifs, line);
    net.size = std::stoi(line.substr(7, 1));
    for (int i = 0; i < net.size; i++)
    {
        getline(ifs, line);
        net.pins[i] = std::stoi(line.substr(5, 1));
    }
}
void parseNumNet(Net* net1, Net* net2, Net* net3, NumNets& numnets)
{
    numnets.nets[0] = net1;
    numnets.nets[1] = net2;
    numnets.nets[2] = net3;
}
