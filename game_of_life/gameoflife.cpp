// gameoflife.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "conio.h"
#include "cabbage.h"
#include "rabbit.h"
#include "wolf.h"
#include <vector>
#include <iostream>
#include <windows.h>
#include <SFML/Graphics.hpp>


using namespace std;


void main()
{
	const int max_count_abc = 3000;
	int count_cabbage = 10;
	int count_rabbit = 13;
	int count_wolf = 12;
	int new_abc_p = 0;
	int count_abc = 0;
	int k = 0;
	int k1 = 0;
	const int count_of_step = 1000;
	const int size_x = 40;
	const int size_y = 60;
	bool pr = false;
	bool gl_pr = false;
	abc* abc_mas[max_count_abc];
	vector<bool>abc_del;
	_getch();
	sf::RenderWindow window(sf::VideoMode(600, 900), "MyKitchen-garden");
	sf::Texture cab_tex1;
	sf::Texture cab_tex2;
	sf::Texture cab_tex3;
	cab_tex1.loadFromFile("images/cabbage.png");
	cab_tex2.loadFromFile("images/rabbit.png");
	cab_tex3.loadFromFile("images/wolf2.png");
	count_abc = count_cabbage + count_rabbit + count_wolf;
	for (int i = 0; i < count_cabbage; i++)
	{
		abc_mas[i] = new cabbage;
		abc_del.push_back(false);
	}
	for (int i = count_cabbage; i < count_cabbage + count_rabbit; i++)
	{
		abc_mas[i] = new rabbit;
		abc_del.push_back(false);
	}
	for (int i = count_cabbage + count_rabbit; i < count_abc; i++)
	{
		abc_mas[i] = new wolf;
		abc_del.push_back(false);
	}
	for (int step = 1; step < count_of_step; step++)
	{
		//кол-во равно кол-во + размножение
		cout << step << endl;
		count_abc += new_abc_p;
		new_abc_p = 0;
		k = 0;	
		cout << count_abc << endl;
		//объект рисования
		sf::Sprite cab_spr[3000];
		
		//в начала abc_mas кладем реальные элементы, k1 настоящая длина, count_cabbage бывшая с мусоров
		for (int i = 0; i < count_abc; i++)
			if (abc_del[i] == false)
			{
				abc_mas[k1] = abc_mas[i];
				k1++;
			}	
		
		//реальные элементы в false
		for (int i = 0; i < k1; i++)
			abc_del[i] = false;
		//удаляем мусор, с k1 по count (не удаляется)
		/*for (int i = k1; i < count_cabbage; i++)
			delete abc_mas[i];*/
		abc_del.resize(k1);
		
		count_abc = k1;
		k1 = 0;		
		cout << count_abc << endl;
		//запускаем цикл по всем элементам
		for (int i = 0; i < count_abc; i++)
		{
			gl_pr = false;
			pr = false;
			cout << abc_mas[i]->GetBirth() << abc_mas[i]->life(step) << abc_mas[i]->reproduction(step) << abc_mas[i]->GetAnim() << endl;
			//если жизнь правда, то del правда 
			if (abc_mas[i]->life(step) == true)
				abc_del[i] = true;
			//если размножение правда, то плюс элемент в конец
			if (abc_mas[i]->reproduction(step) == true)
			{
				//cabbage current_cabbage(step);				
				if (abc_mas[i]->GetAnim() == 1)
					//abc_mas[count_abc + new_abc_p] = new cabbage(step);
					abc_mas[count_abc + new_abc_p] = new cabbage(abc_mas[i]->GetX() + rand() % 10 - 5, abc_mas[i]->GetY() + rand() % 10 - 5, step);
				else if (abc_mas[i]->GetAnim() == 2)
					//abc_mas[count_abc + new_abc_p] = new rabbit(step);
				{
					abc_mas[count_abc + new_abc_p] = new rabbit(abc_mas[i]->GetX() + rand() % 2 + 2, abc_mas[i]->GetY() + rand() % 2 + 2, step);
					abc_mas[count_abc + new_abc_p] = new rabbit(abc_mas[i]->GetX() + rand() % 2 - 3, abc_mas[i]->GetY() + rand() % 2 - 3, step);
				}
				else if (abc_mas[i]->GetAnim() == 3)
					abc_mas[count_abc + new_abc_p] = new cabbage(abc_mas[i]->GetX() + rand() % 2 + 2, abc_mas[i]->GetY() + rand() % 2 + 2, step);
				abc_del.push_back(false);
				new_abc_p++;				
			}

			//поедание капусты
			if (abc_mas[i]->GetAnim() == 2)
				for (int j = 0; j < count_abc; j++)
				{
					if (abc_mas[j]->GetAnim() == 1)
					{
						if ((abc_mas[j]->GetX() == abc_mas[i]->GetX() + 1) & (abc_mas[j]->GetY() == abc_mas[i]->GetY() + 1))
						{
							abc_del[j] = true;
							abc_mas[i]->moveH();
							abc_mas[i]->moveR();
							gl_pr = true;
						}
						if ((abc_mas[j]->GetX() == abc_mas[i]->GetX() + 1) & (abc_mas[j]->GetY() == abc_mas[i]->GetY()))
						{
							abc_del[j] = true;
							abc_mas[i]->moveR();
							gl_pr = true;
						}
						if ((abc_mas[j]->GetX() == abc_mas[i]->GetX() + 1) & (abc_mas[j]->GetY() == abc_mas[i]->GetY() - 1))
						{
							abc_del[j] = true;
							abc_mas[i]->moveD();
							abc_mas[i]->moveR();
							gl_pr = true;
						}
						if ((abc_mas[j]->GetX() == abc_mas[i]->GetX() - 1) & (abc_mas[j]->GetY() == abc_mas[i]->GetY() + 1))
						{
							abc_del[j] = true;
							abc_mas[i]->moveH();
							abc_mas[i]->moveL();
							gl_pr = true;
						}
						if ((abc_mas[j]->GetX() == abc_mas[i]->GetX() - 1) & (abc_mas[j]->GetY() == abc_mas[i]->GetY()))
						{
							abc_del[j] = true;
							abc_mas[i]->moveL();
							gl_pr = true;
						}
						if ((abc_mas[j]->GetX() == abc_mas[i]->GetX() - 1) & (abc_mas[j]->GetY() == abc_mas[i]->GetY() - 1))
						{
							abc_del[j] = true;
							abc_mas[i]->moveD();
							abc_mas[i]->moveL();
							gl_pr = true;
						}
						if ((abc_mas[j]->GetX() == abc_mas[i]->GetX()) & (abc_mas[j]->GetY() == abc_mas[i]->GetY() + 1))
						{
							abc_del[j] = true;
							abc_mas[i]->moveH();
							gl_pr = true;
						}
						if ((abc_mas[j]->GetX() == abc_mas[i]->GetX()) & (abc_mas[j]->GetY() == abc_mas[i]->GetY() - 1))
						{
							abc_del[j] = true;
							abc_mas[i]->moveD();
							gl_pr = true;
						}
					}
				}
			//поедание кроликов
			if (abc_mas[i]->GetAnim() == 3)
				for (int j = 0; j < count_abc; j++)
				{
					if (abc_mas[j]->GetAnim() == 2)
					{
						if ((abc_mas[j]->GetX() == abc_mas[i]->GetX() + 1) & (abc_mas[j]->GetY() == abc_mas[i]->GetY() + 1))
						{
							abc_del[j] = true;
							abc_mas[i]->moveH();
							abc_mas[i]->moveR();
							gl_pr = true;
						}
						if ((abc_mas[j]->GetX() == abc_mas[i]->GetX() + 1) & (abc_mas[j]->GetY() == abc_mas[i]->GetY()))
						{
							abc_del[j] = true;
							abc_mas[i]->moveR();
							gl_pr = true;
						}
						if ((abc_mas[j]->GetX() == abc_mas[i]->GetX() + 1) & (abc_mas[j]->GetY() == abc_mas[i]->GetY() - 1))
						{
							abc_del[j] = true;
							abc_mas[i]->moveD();
							abc_mas[i]->moveR();
							gl_pr = true;
						}
						if ((abc_mas[j]->GetX() == abc_mas[i]->GetX() - 1) & (abc_mas[j]->GetY() == abc_mas[i]->GetY() + 1))
						{
							abc_del[j] = true;
							abc_mas[i]->moveH();
							abc_mas[i]->moveL();
							gl_pr = true;
						}
						if ((abc_mas[j]->GetX() == abc_mas[i]->GetX() - 1) & (abc_mas[j]->GetY() == abc_mas[i]->GetY()))
						{
							abc_del[j] = true;
							abc_mas[i]->moveL();
							gl_pr = true;
						}
						if ((abc_mas[j]->GetX() == abc_mas[i]->GetX() - 1) & (abc_mas[j]->GetY() == abc_mas[i]->GetY() - 1))
						{
							abc_del[j] = true;
							abc_mas[i]->moveD();
							abc_mas[i]->moveL();
							gl_pr = true;
						}
						if ((abc_mas[j]->GetX() == abc_mas[i]->GetX()) & (abc_mas[j]->GetY() == abc_mas[i]->GetY() + 1))
						{
							abc_del[j] = true;
							abc_mas[i]->moveH();
							gl_pr = true;
						}
						if ((abc_mas[j]->GetX() == abc_mas[i]->GetX()) & (abc_mas[j]->GetY() == abc_mas[i]->GetY() - 1))
						{
							abc_del[j] = true;
							abc_mas[i]->moveD();
							gl_pr = true;
						}
					}
				}

			//погоня за капустой
			if ((abc_mas[i]->GetAnim() == 2) & (gl_pr == false))
				for (int j = 0; j < count_abc; j++)
					if (pr == false)
					{
						if ((abc_mas[j]->GetAnim() == 1) & (abs(abc_mas[i]->GetX() - abc_mas[j]->GetX()) <= 4) & (abs(abc_mas[i]->GetY() - abc_mas[j]->GetY()) <= 4))
						{							
							if ((abc_mas[i]->GetX() >= abc_mas[j]->GetX()) & (abc_mas[i]->GetY() <= abc_mas[j]->GetY()))
								abc_mas[i]->moveH();
							else if ((abc_mas[i]->GetX() >= abc_mas[j]->GetX()) & (abc_mas[i]->GetY() >= abc_mas[j]->GetY()))
								abc_mas[i]->moveL();
							else if ((abc_mas[i]->GetX() <= abc_mas[j]->GetX()) & (abc_mas[i]->GetY() >= abc_mas[j]->GetY()))
								abc_mas[i]->moveD();
							else if ((abc_mas[i]->GetX() <= abc_mas[j]->GetX()) & (abc_mas[i]->GetY() <= abc_mas[j]->GetY()))
								abc_mas[i]->moveR();
							pr = true;
						}
					}
			
			//погоня за кроликом
			if ((abc_mas[i]->GetAnim() == 3) & (gl_pr == false))
				for (int j = 0; j < count_abc; j++)
					if (pr == false)
					{
						if ((abc_mas[j]->GetAnim() == 2) & (abs(abc_mas[i]->GetX() - abc_mas[j]->GetX()) <= 5) & (abs(abc_mas[i]->GetY() - abc_mas[j]->GetY()) <= 5))
						{
							if ((abc_mas[i]->GetX() >= abc_mas[j]->GetX()) & (abc_mas[i]->GetY() <= abc_mas[j]->GetY()))
								abc_mas[i]->moveH();
							else if ((abc_mas[i]->GetX() >= abc_mas[j]->GetX()) & (abc_mas[i]->GetY() >= abc_mas[j]->GetY()))
								abc_mas[i]->moveL();
							else if ((abc_mas[i]->GetX() <= abc_mas[j]->GetX()) & (abc_mas[i]->GetY() >= abc_mas[j]->GetY()))
								abc_mas[i]->moveD();
							else if ((abc_mas[i]->GetX() <= abc_mas[j]->GetX()) & (abc_mas[i]->GetY() <= abc_mas[j]->GetY()))
								abc_mas[i]->moveR();
							pr = true;
						}
					}

			//хождение кролика рандомное
			if (((abc_mas[i]->GetAnim() == 2) & (gl_pr == false)) || ((abc_mas[i]->GetAnim() == 3) & (gl_pr == false)))
				abc_mas[i]->movement();

			//рисование элемента, переменная k для рисования
			if (abc_mas[i]->GetAnim() == 1)
				if (abc_del[i] == false)
					cab_spr[k].setTexture(cab_tex1);
			if (abc_mas[i]->GetAnim() == 2)
				if (abc_del[i] == false)
					cab_spr[k].setTexture(cab_tex2);
			if (abc_mas[i]->GetAnim() == 3)
				cab_spr[k].setTexture(cab_tex3);
			cab_spr[k].setPosition(abc_mas[i]->GetX() * 15, abc_mas[i]->GetY() * 15);
			k++;
		}	
		for (int i = 0; i < abc_del.size(); i++)
			cout << abc_del[i];
		cout << endl;
		
		//очистка окна и вывод всех элементов рисования
		window.clear();
		for (int i = 0; i < k; i++)
			window.draw(cab_spr[i]);
		window.display();
		Sleep(100);
		//_getch();
	}
	_getch();
}

