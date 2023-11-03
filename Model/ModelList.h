#pragma once

class ModelList {
private:
	ModelList();
	~ModelList();

private:
	static ModelList* m_instance;

public:
	static ModelList* GetInstance();
	static void Destroy();

private:
	const std::string m_defaultFilePath{ ".\\ObjModel\\" };

	// ¸ðµ¨µéÀ» ÀúÀåÇÒ ¸Ê °´Ã¼ »ý¼º
	std::unordered_map<std::string, std::shared_ptr<class Model>> m_modelList{ };

	int m_currentDrawMode{ };

public:
	std::shared_ptr<class Model> GetModel(const std::string& key) const;

	int GetCurrentDrawMode() const;
	void SetDrawModes(int drawMode);

public:
	void Init();
	void LoadModel(const std::string& objectFilePath);
	void LoadModelFromFile(const std::string& modelsFilePath);
};