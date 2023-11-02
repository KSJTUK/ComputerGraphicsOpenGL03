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
	// 모델 내부의 쉐이더 초기화에 필요한 프로그램 ID
	unsigned int m_shaderProgramID{ };

	// 모델들을 저장할 맵 객체 생성
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