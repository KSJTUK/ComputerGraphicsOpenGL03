#pragma once

class ModelList {
private:
	ModelList();
	~ModelList();

private:
	static ModelList* m_instance;

public:
	static ModelList* GetInst();
	static void Destroy();

private:
	// �� ������ ���̴� �ʱ�ȭ�� �ʿ��� ���α׷� ID
	unsigned int m_shaderProgramID{ };

	// �𵨵��� ������ �� ��ü ����
	std::unordered_map<std::string, std::shared_ptr<class Model>> m_modelList{ };

	int m_currentDrawMode{ };

public:
	std::shared_ptr<class Model> GetModel(const std::string& key) const;

	int GetCurrentDrawMode() const;
	void SetDrawModes(int drawMode);

public:
	void Init(unsigned int m_shaderProgramID);
	void LoadModel(const std::string& objectFilePath);
	void LoadModelFromFile(const std::string& modelsFilePath);
};