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
  std::ifstream file("..//cell.cpi");

  if (file.is_open())
  {
      while (!file.eof())
      {
          std:string line;
          getline(file, line);
          if (line.find(".ENDS") != std::string::npos)
          {
              continue;
          }
          if (line.find("MM") != std::string::npos)
          {
              mos new_mos;
              char name[10] ,source[10], gate[10],drain[10] ,temp[10];
              char unit;

              std::sscanf(line.c_str(), "%s %s %s %s %*s %s l=%lfn w=%lf%c",name,
                     source,gate,drain,temp,&new_mos.w_length,&new_mos.w_width,&unit);
              new_mos.m_name = name;
              new_mos.m_source = source;
              new_mos.m_gate = gate;
              new_mos.m_drain = drain;
              if(temp[0]=='n'){
                  new_mos.m_sort=1;
              }
              else if(temp[0]=='p'){
                  new_mos.m_sort=0;
              }
              if(unit=='n'){
                  new_mos.w_width*=1000;
              }

          }
      }
      file.close();
  }
  else
  {
    std::cout << "Unable to open file." << std::endl;
  }



}

