/*
7.设圆半径r=1.5,圆柱高h=3,求圆周长、圆面积、
圆球表面积、圆球体积、圆柱体积。
用scanf输入数据，输出计算结果，
输出时要求有文字说明，取小数点后2位数字。请编程序。
*/

#include <stdio.h>
#include <math.h>

#define pi 3.14159

double radius,height;

int main(){
  //输入数据
  printf("====圆，圆球与圆柱计算程序====\n");
  printf("请输入圆的半径r=");
  scanf("%lf",&radius);
  printf("请输入圆柱体的高h=");
  scanf("%lf",&height);
  //计算过程
  double circle_perimeter = 2 * pi * radius;
  double circle_area = pi * pow(radius,2);
  double sphere_area = 4 * pi * pow(radius,2);
  double sphere_volume = (4.0/3.0) * pi * pow(radius,3);
  double cylinder_volume = circle_area * height;

  //结果输出
  printf("===========计算结果===========\n");
  printf("圆周长为%.2f\n",circle_perimeter);
  printf("圆面积为%.2f\n",circle_area);
  printf("圆球表面积为%.2f\n",sphere_area);
  printf("圆球体积为%.2f\n",sphere_volume);
  printf("圆柱体积为%.2f\n",cylinder_volume);


  return 0;
}
