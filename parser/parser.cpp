//
// Created by Defender on 2024/3/10.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../datebase/datebase.h"




void parser::parser()
{
  std::ifstream file("C:/Users/Defender/Desktop/cells.txt"); // 替换为实际的文件路径

  if (file.is_open())
  {
      std::getline(file, 1);
      while()
      {
          std::getline(file, 1);
          mos new_mos;
          std::string temp;
          char unit;
          file.get(new_mos.m_name);
          file.get(new_mos.m_source);
          file.get(new_mos.m_gate);
          file.get(new_mos.m_drain);
          fiel.get();
          file.get(temp);
          if(temp[0]=='n'){
              new_mos.m_sort=1;
          }
          else if(temp[0]=='p'){
              new_mos.m_sort=0;
          }
          fscanf_s(file,"l=%fn",&new_mos.w_wide);
          fscanf_s(file,"w=%f%c",&new_mos.m_long,&unit);
          if(unit=='n')
              new_mos.m_long*=1000;


      }
      file.close();
  }
  else
  {
    std::cout << "Unable to open file." << std::endl;
  }


  return 0;
}

