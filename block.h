#ifndef BLOCK_H
#define BLOCK_H
#include <SDL2/SDL.h>
#include <iostream>
#include <random>
#include <memory>

// 头文件memory 创建指针用来存储当前方块
template <typename T>
std::unique_ptr<T> currentBlock = std::make_unique<T>();

// 508*840   12*42   20*42  背景图
class backgroundcell
{
public:
  int x, y;
  const int height = 42;
  const int width = 42;
  backgroundcell(int row, int col)
  {
    x = col * width;
    y = row * height;
  }

  backgroundcell() : x(0), y(0) {} // 添加默认构造函数

  // 显式定义复制构造函数
  backgroundcell(const backgroundcell &other)
  {
    x = other.x; // 深拷贝成员变量
    y = other.y;
  }

  // 显式定义赋值运算符
  backgroundcell &operator=(const backgroundcell &other)
  {
    x = other.x; // 深拷贝成员变量
    y = other.y;
    return *this;
  }
};

class Shape // 所有图形的基类
{
public:
  virtual ~Shape() = default;
  virtual int (*getCurrentBlock(int rotation))[4] { return nullptr; };
  int rotation = 0;  // 当状态前旋转
  bool drop = false; // 当前下落状态

  int block1[4][4], block2[4][4], block3[4][4], block4[4][4];

  int getRotation() const { return rotation; }
};

// 所有图形均按照顺时针旋转顺序排列

// 长条形
class rectangle : public Shape
{
public:
  int (*getCurrentBlock(int rotation))[4]
  {
    switch (rotation)
    {
    case 0:
      return block1;
    case 1:
      return block2;
    case 2:
      return block3;
    case 3:
      return block4;
    }
    return block1;
  }
  int block1[4][4] = {{0, 0, 1, 0},
                      {0, 0, 1, 0},
                      {0, 0, 1, 0},
                      {0, 0, 1, 0}};
  int block2[4][4] = {{1, 1, 1, 1},
                      {0, 0, 0, 0},
                      {0, 0, 0, 0},
                      {0, 0, 0, 0}};
  int block3[4][4] = {{0, 0, 1, 0},
                      {0, 0, 1, 0},
                      {0, 0, 1, 0},
                      {0, 0, 1, 0}};
  int block4[4][4] = {{1, 1, 1, 1},
                      {0, 0, 0, 0},
                      {0, 0, 0, 0},
                      {0, 0, 0, 0}};
};
// 左L
class leftL : public Shape
{
public:
  int (*getCurrentBlock(int rotation))[4]
  {
    switch (rotation)
    {
    case 0:
      return block1;
    case 1:
      return block2;
    case 2:
      return block3;
    case 3:
      return block4;
    }
    return block1;
  }

  int block1[4][4] = {{0, 1, 0, 0},
                      {0, 1, 0, 0},
                      {1, 1, 0, 0},
                      {0, 0, 0, 0}};
  // 顺时针旋转
  int block2[4][4] = {{1, 0, 0, 0},
                      {1, 1, 1, 0},
                      {0, 0, 0, 0},
                      {0, 0, 0, 0}};
  int block3[4][4] = {{1, 1, 0, 0},
                      {1, 0, 0, 0},
                      {1, 0, 0, 0},
                      {0, 0, 0, 0}};
  int block4[4][4] = {{1, 1, 1, 0},
                      {0, 0, 1, 0},
                      {0, 0, 0, 0},
                      {0, 0, 0, 0}};
};
// 右L
class rightL : public Shape
{
public:
  int (*getCurrentBlock(int rotation))[4]
  {
    switch (rotation)
    {
    case 0:
      return block1;
    case 1:
      return block2;
    case 2:
      return block3;
    case 3:
      return block4;
    }
    return block1;
  }

  int block1[4][4] = {{1, 0, 0, 0},
                      {1, 0, 0, 0},
                      {1, 1, 0, 0},
                      {0, 0, 0, 0}};
  // 顺时针旋转
  int block2[4][4] = {{1, 1, 1, 0},
                      {1, 0, 0, 0},
                      {0, 0, 0, 0},
                      {0, 0, 0, 0}};
  int block3[4][4] = {{1, 1, 0, 0},
                      {0, 1, 0, 0},
                      {0, 1, 0, 0},
                      {0, 0, 0, 0}};
  int block4[4][4] = {{0, 0, 1, 0},
                      {1, 1, 1, 0},
                      {0, 0, 0, 0},
                      {0, 0, 0, 0}};
};
// 方块
class square : public Shape
{
public:
  int (*getCurrentBlock(int rotation))[4]
  {
    switch (rotation)
    {
    case 0:
      return block1;
    case 1:
      return block2;
    case 2:
      return block3;
    case 3:
      return block4;
    }
    return block1;
  }

  int block1[4][4] = {{1, 1, 0, 0},
                      {1, 1, 0, 0},
                      {0, 0, 0, 0},
                      {0, 0, 0, 0}};
  int block2[4][4] = {{1, 1, 0, 0},
                      {1, 1, 0, 0},
                      {0, 0, 0, 0},
                      {0, 0, 0, 0}};
  int block3[4][4] = {{1, 1, 0, 0},
                      {1, 1, 0, 0},
                      {0, 0, 0, 0},
                      {0, 0, 0, 0}};
  int block4[4][4] = {{1, 1, 0, 0},
                      {1, 1, 0, 0},
                      {0, 0, 0, 0},
                      {0, 0, 0, 0}};
};
// 左Z
class leftZ : public Shape
{
public:
  int (*getCurrentBlock(int rotation))[4]
  {
    switch (rotation)
    {
    case 0:
      return block1;
    case 1:
      return block2;
    case 2:
      return block3;
    case 3:
      return block4;
    }
    return block1;
  }

  int block1[4][4] = {{1, 1, 0, 0},
                      {0, 1, 1, 0},
                      {0, 0, 0, 0},
                      {0, 0, 0, 0}};
  int block2[4][4] = {{0, 0, 1, 0},
                      {0, 1, 1, 0},
                      {0, 1, 0, 0},
                      {0, 0, 0, 0}};
  int block3[4][4] = {{1, 1, 0, 0},
                      {0, 1, 1, 0},
                      {0, 0, 0, 0},
                      {0, 0, 0, 0}};
  int block4[4][4] = {{0, 0, 1, 0},
                      {0, 1, 1, 0},
                      {0, 1, 0, 0},
                      {0, 0, 0, 0}};
};
// 右Z
class rightZ : public Shape
{
public:
  int (*getCurrentBlock(int rotation))[4]
  {
    switch (rotation)
    {
    case 0:
      return block1;
    case 1:
      return block2;
    case 2:
      return block3;
    case 3:
      return block4;
    }
    return block1;
  }

  int block1[4][4] = {{0, 1, 1, 0},
                      {1, 1, 0, 0},
                      {0, 0, 0, 0},
                      {0, 0, 0, 0}};
  int block2[4][4] = {{1, 0, 0, 0},
                      {1, 1, 0, 0},
                      {0, 1, 0, 0},
                      {0, 0, 0, 0}};
  int block3[4][4] = {{0, 1, 1, 0},
                      {1, 1, 0, 0},
                      {0, 0, 0, 0},
                      {0, 0, 0, 0}};
  int block4[4][4] = {{1, 0, 0, 0},
                      {1, 1, 0, 0},
                      {0, 1, 0, 0},
                      {0, 0, 0, 0}};
};
// 丁字型
class ding : public Shape
{
public:
  int (*getCurrentBlock(int rotation))[4]
  {
    switch (rotation)
    {
    case 0:
      return block1;
    case 1:
      return block2;
    case 2:
      return block3;
    case 3:
      return block4;
    }
    return block1;
  }

  int block1[4][4] = {{1, 1, 1, 0},
                      {0, 1, 0, 0},
                      {0, 0, 0, 0},
                      {0, 0, 0, 0}};
  int block2[4][4] = {{0, 1, 0, 0},
                      {1, 1, 0, 0},
                      {0, 1, 0, 0},
                      {0, 0, 0, 0}};
  int block3[4][4] = {{0, 1, 0, 0},
                      {1, 1, 1, 0},
                      {0, 0, 0, 0},
                      {0, 0, 0, 0}};
  int block4[4][4] = {{1, 0, 0, 0},
                      {1, 1, 0, 0},
                      {1, 0, 0, 0},
                      {0, 0, 0, 0}};
};

std::unique_ptr<Shape> getRandomShape()
{
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_int_distribution<> dis(0, 6);

  int shaprIndex = dis(gen);
  switch (shaprIndex)
  {
  case 0:
    return std::make_unique<rectangle>();
  case 1:
    return std::make_unique<square>();
  case 2:
    return std::make_unique<leftL>();
  case 3:
    return std::make_unique<rightL>();
  case 4:
    return std::make_unique<leftZ>();
  case 5:
    return std::make_unique<rightZ>();
  case 6:
    return std::make_unique<ding>();
  default:
    return std::make_unique<rectangle>();
  }
}

#endif