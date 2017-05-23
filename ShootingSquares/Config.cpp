#include "AllHeaders.h"

/// Getters

RESOLUTION Config::getRes() const
{
	return  ConfigResolution;
}
VOLUME Config::getVol() const
{
	return ConfigVolume;
}

/// Setters

void Config::ChangeAllConfig(RESOLUTION customRes, VOLUME customVol)
{
	ChangeResolution(customRes);
	ChangeVolume(customVol);

}
void Config::ChangeResolution(RESOLUTION customRes)
{
	ConfigResolution = customRes;
}
void Config::ChangeVolume(VOLUME customVol)
{
	ConfigVolume = customVol;
}


void Config::CheckFileCorrection()
{
	if (Tools::FileExist("Config\\configs.cfg"))
	{
		File.open("Config\\configs.cfg", ios_base::in);
		if (File.is_open())
		{
			File >> this->ConfigResolution.WIDTH;
			File >> this->ConfigResolution.HEIGHT;
			File >> this->ConfigVolume.EFFECTS;
			File >> this->ConfigVolume.MUSIC;

			File.close();

			CONFIGURED = true;
		}
		else
			Tools::DebugMessageBox("Failed to open file!");
	}
	else
	{
		Tools::DebugMessageBox("Config file not found!\nCreating Default.");

		File.open("Config\\configs.cfg", ios_base::out);
		if (File.is_open())
		{
			File << this->ConfigResolution.WIDTH << endl;
			File << this->ConfigResolution.HEIGHT << endl;
			File << this->ConfigVolume.EFFECTS << endl;
			File << this->ConfigVolume.MUSIC << endl;
			File.close();
		}
		else
			Tools::DebugMessageBox("Failed to open file!");
	}

	// Just in case something happens
	if (File.is_open())
		File.close();
}

Config::Config()
{
	CheckFileCorrection();
}
