//
// Created by spiderman on 24-3-10.
//
#pragma once
#ifndef PROJECT_DATABASE_H
#define PROJECT_DATABASE_H

#include <iostream>
#include <vector>
#include <string>

class mos
{
 public:
  mos() {}
  mos(const mos& mos_i) : m_sort(mos_i.m_sort), m_name(mos_i.m_name), m_source(mos_i.m_source),
                          m_gate(mos_i.m_gate), m_drain(mos_i.m_drain), w_width(mos_i.w_width),
                          w_length(mos_i.w_length), m_x(mos_i.m_x), m_f(mos_i.m_f) {}

  ~mos() =  default;

  std::string m_name;
  int m_sort;
  std::string m_source;
  std::string m_gate;
  std::string m_drain;
  float w_width;
  float w_length;
  int m_x; // x_loc
  int m_f; // is_roll
};

class net
{
  int num_pmos;
  std::vector<mos> pmos;
  int num_nmos;
  std::vector<mos> nmos;
};

#endif //PROJECT_DATABASE_H
