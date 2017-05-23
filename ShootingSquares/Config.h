#pragma once

using namespace std;
using namespace sf;

class Config
{
private:

	// Localization of saved configs
	string ConfigFilePath;
	fstream File;

	// Properties
	RESOLUTION ConfigResolution;
	VOLUME ConfigVolume;

	// Flag chcecking if configs has been already applied 
	// called on start
	bool CONFIGURED = false;

public:

	/// Getters

	RESOLUTION getRes() const;
	VOLUME getVol() const;

	/// Setters

	void ChangeAllConfig(RESOLUTION customRes, VOLUME customVol);
	void ChangeResolution(RESOLUTION customRes);
	void ChangeVolume(VOLUME customVol);

	/// Initialization

	void CheckFileCorrection();

	Config();
};

