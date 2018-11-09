#pragma once

class Menu
{
public:
	Menu(int itemCount, char** itemList, void back(int index), void forward(int index));
	~Menu();
	void handleInput(bool up, bool right, bool down, bool left);

	int getSelectedIndex();
	char* getItem(int index);
	int getItemCount();

	void queueRepaint();
	bool requiresRepaint();

private:
	bool repaint;
	int selectedIndex;
	int itemCount;
	char** itemList;
	void(*back) (int index);
	void(*forward) (int index);
};

