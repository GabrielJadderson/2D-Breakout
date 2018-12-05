#pragma once

class ResourceSerializer
{
private:

public:
	ResourceSerializer();

	static void WriteToDisk(const std::string& file, const ResourceData& rd);
	static void Save(ResourceBlock& block);
	static void Load(ResourceBlock& block);

	static void Stream(ResourceBlock& block);
	static ResourceData GetFromStream(const std::string& resourceName, ResourceBlock& block);
	static std::vector<byte> StreamDirect(const std::string& resourceName, ResourceBlock& block);

	static ResourceData Get(const std::string& resourceName, const ResourceBlock& block);
	static int GetLocation(const std::string& resourceName, const ResourceBlock& block);

	static void Add(const std::string& filepath, const std::string& resourceName, ResourceType type, ResourceBlock& block);
	static void Delete(const std::string& resourceName, ResourceBlock& block);

	static ResourceBlock& CreateResourceBlock(const std::string& filepath, DatType type);
	static void DeleteBlock(ResourceBlock* rb);

	~ResourceSerializer();
};
