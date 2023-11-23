#pragma once

class WorldScene abstract {
public:
	WorldScene() { }
	virtual ~WorldScene() { }

protected:

public:
	virtual void Init() = 0;
	virtual void Input(unsigned char key, bool down) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
};


class WorldSceneSolarSys {
public:
	WorldSceneSolarSys() { }
	~WorldSceneSolarSys() { }

private:
	

};

class WorldScene1 : public WorldScene {
public:
	WorldScene1();
	~WorldScene1();

private:
	std::unique_ptr<class Cube> m_earth{ };
	std::unique_ptr<class Cube> m_moon{ };
	std::unique_ptr<class Cube> m_mars{ };

	std::unique_ptr<class Terrain> m_ground{ };

	std::vector<std::unique_ptr<class Cube>> m_spheres{ };
	std::unique_ptr<class LightObject> m_lightObject{ };

	std::unique_ptr<class ParticleSystem> m_particleSystem{ };

public:
	void Init();
	void Input(unsigned char key, bool down);
	void Update(float deltaTime);
	void Render();
};