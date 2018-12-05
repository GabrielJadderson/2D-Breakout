#pragma once

namespace binary_serialization
{
	using namespace std;
	using byte = unsigned char;

	enum BinaryDataType : char //the different types of (binary files/.dat files) supported, each with different signature
	{
		Resource = 1,
		Library = 2,
	};

	enum BinaryResourceType : char //the different type of resources contained in a binary file.
	{
		None = 0,
		LevelData = 1,
		Scene = 2,
		Save = 3,
		Texture = 4,
		Font = 5,
		Config = 6
	};

	struct BinaryNode
	{
		string Name{};
		BinaryResourceType Type = BinaryResourceType::None;
		vector<byte> Data{};

		template <class Archive>
		void serialize(Archive & ar)
		{
			ar(Name, Type, Data);
		}
	};

	struct BinaryBlock
	{
		BinaryDataType Type;
		string FilePath;
		vector<BinaryNode> Resources;

		template <class Archive>
		void serialize(Archive & ar)
		{
			ar(Type, FilePath, Resources);
		}
	};


	class BinarySerializer
	{
	public:
		BinarySerializer();
		~BinarySerializer();

		static void Load(BinaryBlock& block);
		static void Save(BinaryBlock& block);
		static BinaryBlock& CreateBinaryBlock(const string& filepath, BinaryDataType type);
	};

}
