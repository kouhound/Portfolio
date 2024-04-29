#pragma once
enum  scene {
	TITLE=0,
	GAME,
	MAX
};
scene getCursvene();
scene getNextscene();
void StartSC(scene);
void SetSC();
