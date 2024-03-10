//
// Created by Defender on 2024/3/10.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
  std::ifstream file("C:/Users/Defender/Desktop/cells.txt"); // 替换为实际的文件路径

  if (file.is_open()) {
    std::vector<std::string> lines; // 存储每行数据的vector
    std::string line;

    while (std::getline(file, line)) {
      lines.push_back(line);
    }

    // 打印存储在vector中的所有行
    for (const auto &line : lines) {
      std::cout << line << std::endl;
    }

    file.close();
  }
  else {
    std::cout << "Unable to open file." << std::endl;
  }

  return 0;
}

