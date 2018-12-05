#include "pch.h"


ResourceSerializer::ResourceSerializer()
{

	//WriteCereal();
	//ReadCereal();

	//auto rb = load_binary_file("test.dat");
	//BenchTimer bt;
	//ResourceBlock block = CreateResourceBlock("resources/resources.bin", DatType::Resource);

	/*
	Add("resources/sprites/breakout_custom.png", "breakout_custom.png", ResourceType::Texture, block);
	Add("resources/sprites/breakout_pieces.png", "breakout_pieces.png", ResourceType::Texture, block);
	Add("resources/sprites/more_breakout_pieces.png", "more_breakout_pieces.png", ResourceType::Texture, block);
	Add("resources/textures/balls_8x8.png", "balls_8x8.png", ResourceType::Texture, block);
	Add("resources/textures/bricks_32x16.png", "bricks_32x16.png", ResourceType::Texture, block);
	Add("resources/textures/hearts_10x9.png", "hearts_10x9.png", ResourceType::Texture, block);
	Add("resources/textures/platform_large_64x16.png", "platform_large_64x16.png", ResourceType::Texture, block);
	Add("resources/textures/platform_locked_64x20.png", "platform_locked_64x20.png", ResourceType::Texture, block);
	Add("resources/textures/platform_small_32x16.png", "platform_small_32x16.png", ResourceType::Texture, block);
	Add("resources/fonts/Squarebit.ttf", "Squarebit.ttf", ResourceType::Texture, block);
	Add("resources/fonts/Squarebit2Px.ttf", "Squarebit2Px.ttf", ResourceType::Texture, block);


	Save(block);
	bt.StopAndPrint();

	*/


	//Load(block);

	//auto data = Get("platform_locked_64x20.png", block);
	//bt.StopAndPrint();
	//ResourceBlock block2 = Stream("resources/resources.bin");

	/*
	ResourceBlock block4;
	__int64 sstart = 0;
	__int64 eend = 0;
	sstart = GetCpuClocks();

	Stream(block);

	eend = GetCpuClocks();
	std::cout << "[BenchTime]: " << (eend - sstart) / CLOCKS_PER_SEC << " (Ticks pr second (tps)), " << eend - sstart << " (Total ticks)" << std::endl;



	ResourceData data2;
	sstart = GetCpuClocks();

	data2 = GetFromStream("platform_locked_64x20.png", block4);

	eend = GetCpuClocks();
	std::cout << "[BenchTime]: " << (eend - sstart) / CLOCKS_PER_SEC << " (Ticks pr second (tps)), " << eend - sstart << " (Total ticks)" << std::endl;

	*/

	//WriteToDisk("platform_locked_64x20.png", data);
	//WriteToDisk(block.Resources[0], block.MetaData[0]);

	/*
	std::clock_t    start;
	start = std::clock();
	SaveToBinaryFile("test2.dat", block);
	std::cout << "Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;

	start = std::clock();
	ResourceBlock block2 = LoadFromBinaryFile("test2.dat");
	std::cout << "Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;

	start = std::clock();
	ResourceBlock block23 = StreamFromBinaryFile("test2.dat", "");
	std::cout << "Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
	*/
}


void ResourceSerializer::WriteToDisk(const std::string& file, const ResourceData& rd)
{
	//open stream
	std::ofstream f;
	f.open(file, std::ios::binary | std::ios::out);
	if (f.is_open())
	{
		if (!rd.Data.empty())
		{
			uint64_t size = rd.Data.size();
			f.write((char*)&rd.Data[0], size);
		}
		f.close();
	}
}



void ResourceSerializer::Save(ResourceBlock& block)
{
	//open stream
	std::ofstream f;
	f.open(block.FilePath, std::ios::binary | std::ios::out);

	if (f.is_open())
	{
		//if (block.IsLoaded)
		//{
		if (!block.IsStreamed)
		{
			//### Write the HEADER ###

			//first we write resource block information
			f.write(reinterpret_cast<char*>(&block.Type), 1); //0
			//write the type, and since the type is char we only need to write 1 byte.

			//write the sizes.
			uint64_t entries = block.Resources.size();
			f.write(reinterpret_cast<char*>(&entries), sizeof(uint64_t)); //9


			//#### write metadata #####
			//write types
			uint64_t typePadding = 0;
			for (auto i = 0; i < entries; i++)
			{
				f.write(reinterpret_cast<char*>(&block.MetaData[i].Type), 1);
				typePadding += 1;
			}

			//write names
			uint64_t namePadding = 0;
			for (auto i = 0; i < entries; i++)
			{
				short size = static_cast<short>(block.MetaData[i].Name.size());
				f.write(reinterpret_cast<char*>(&size), sizeof(short));
				f.write(reinterpret_cast<char*>(&(block.MetaData[i].Name[0])), size);
				//max bytes a name can be is 50!!
				namePadding += sizeof(uint64_t) + size;
			}

			std::vector<uint64_t> sizes;
			//write sizes
			uint64_t sizePadding = 0;
			for (auto i = 0; i < entries; i++)
			{
				uint64_t size = block.Resources[i].Data.size();
				f.write(reinterpret_cast<char*>(&size), sizeof(uint64_t));
				sizes.push_back(size);
				sizePadding += sizeof(uint64_t);
			}


			//write locations
			int deltaLoc = static_cast<int>(f.tellp());
			deltaLoc += entries * 4;
			for (auto i = 0; i < entries; i++)
			{
				f.write(reinterpret_cast<char*>(&deltaLoc), sizeof(int));
				deltaLoc += sizes[i];
			}

			//int chewck = f.tellp();
			//write resources vec:
			for (auto i = 0; i < entries; i++)
			{
				f.write(reinterpret_cast<char*>(block.Resources[i].Data.data()), sizes[i]);
				int chewck2 = f.tellp();
			}
			//int chewck23 = f.tellp();
			//write the data in the locations vec:

			f.close();

		}
		else std::cout << "\033[1;31m" << "[ResourceSerializer] BLOCK WAS STREAMED! UNSUPPORTED, EXITING FROM SAVE" << "\033[0m" << std::endl;
		//}
		//else std::cout << "\033[1;31m" << "[ResourceSerializer] BLOCK NOT LOADED!" << "\033[0m" << std::endl;
	}
	else std::cout << "COULDN'T FIND RESOURCE: " << block.FilePath << "\n";
}

void ResourceSerializer::Load(ResourceBlock& block)
{
	std::ifstream f;
	f.open(block.FilePath, std::ios::binary | std::ios::in);


	if (f.is_open())
	{

		if (!block.IsLoaded)
		{
			if (!block.IsStreamed)
			{
				//read type
				f.read(reinterpret_cast<char*>(&(block.Type)), 1); //1 byte type
				//here we could do different things based on the type.

				//read the sizes.
				uint64_t entries = 0;
				f.read(reinterpret_cast<char*>(&(entries)), sizeof(uint64_t)); //8 bytes

				std::vector<ResourceType> types(entries);
				std::vector<std::string> names(entries);
				block.Sizes = std::vector<uint64_t>(entries);
				block.Resources = std::vector<ResourceData>(entries);
				block.Locations = std::vector<int>(entries);

				f.read(reinterpret_cast<char*>(&(types[0])), sizeof(ResourceType) * entries);

				for (auto i = 0; i < entries; i++)
				{
					//allocate data here for metadata, saving us a for loop.
					ResourceMetadata md;
					md.Type = types[i];

					short nameSize = 0;
					f.read(reinterpret_cast<char*>(&(nameSize)), sizeof(short));
					auto out = static_cast<char*>(malloc(nameSize));
					f.read(&out[0], nameSize);

					md.Name = std::string(out, nameSize);
					block.MetaData.push_back(md);
				}

				f.read(reinterpret_cast<char*>(&(block.Sizes[0])), sizeof(uint64_t) * entries);
				f.read(reinterpret_cast<char*>(&(block.Locations[0])), sizeof(int) * entries);

				for (auto i = 0; i < entries; i++)
				{
					//rb.MetaData[i].Location = rb.Locations[i];
					block.Resources[i].Data = std::vector<byte>(block.Sizes[i]);
					f.read(reinterpret_cast<char*>(&(block.Resources[i].Data[0])), block.Sizes[i]);
				}

				block.IsLoaded = true;
				block.IsStreamed = false;
			}
			else std::cout << "\033[1;31m" << "[ResourceSerializer] BLOCK NOT STREAMED!" << "\033[0m" << std::endl;
		}
		else std::cout << "\033[1;31m" << "[ResourceSerializer] BLOCK NOT LOADED!" << "\033[0m" << std::endl;


		f.close();
	}
	else std::cout << "COULDN'T FIND RESOURCE: " << block.FilePath << "\n";
}

void ResourceSerializer::Stream(ResourceBlock& block)
{
	std::ifstream f;
	f.open(block.FilePath, std::ios::binary | std::ios::in);

	if (f.is_open())
	{
		if (!block.IsLoaded)
		{
			if (!block.IsStreamed)
			{

				//read type
				f.read(reinterpret_cast<char*>(&(block.Type)), 1); //1 byte type
				//here we could do different things based on the type.

				//read the sizes.
				uint64_t entries = 0;
				f.read(reinterpret_cast<char*>(&(entries)), sizeof(uint64_t)); //8 bytes


				std::vector<ResourceType> types(entries);
				std::vector<std::string> names(entries);
				block.Sizes = std::vector<uint64_t>(entries);
				block.Resources = std::vector<ResourceData>(entries);
				block.Locations = std::vector<int>(entries);


				f.read(reinterpret_cast<char*>(&(types[0])), sizeof(ResourceType) * entries);

				for (auto i = 0; i < entries; i++)
				{
					//allocate data here for metadata, saving us a for loop.
					ResourceMetadata md;
					md.Type = types[i];

					short nameSize = 0;
					f.read(reinterpret_cast<char*>(&(nameSize)), sizeof(short));
					auto out = static_cast<char*>(malloc(nameSize));
					f.read(&out[0], nameSize);

					md.Name = std::string(out, nameSize);
					block.MetaData.push_back(md);
				}

				f.read(reinterpret_cast<char*>(&(block.Sizes[0])), sizeof(uint64_t) * entries);
				f.read(reinterpret_cast<char*>(&(block.Locations[0])), sizeof(int) * entries);


				block.IsLoaded = true;
				block.IsStreamed = true;
			}
			else std::cout << "\033[1;31m" << "[ResourceSerializer] BLOCK NOT STREAMED!" << "\033[0m" << std::endl;
		}
		else std::cout << "\033[1;31m" << "[ResourceSerializer] BLOCK NOT LOADED!" << "\033[0m" << std::endl;

		f.close();
	}
	else std::cout << "COULDN'T FIND RESOURCE: " << block.FilePath << "\n";
}


int ResourceSerializer::GetLocation(const std::string& resourceName, const ResourceBlock& block)
{
	if (block.IsLoaded)
	{
		if (!block.Resources.empty())
			for (auto i = 0; i < block.MetaData.size(); i++)
				if (block.MetaData[i].Name == resourceName)
					return block.Locations[i];
	}
	else std::cout << "\033[1;31m" << "[ResourceSerializer] BLOCK NOT LOADED!" << "\033[0m" << std::endl;
	return -1;
}

//
ResourceData ResourceSerializer::GetFromStream(const std::string& resourceName, ResourceBlock& block)
{
	std::ifstream f;
	f.open(block.FilePath, std::ios::binary | std::ios::in);

	if (f.is_open())
	{
		if (block.IsLoaded)
		{
			if (block.IsStreamed)
			{
				if (!block.Resources.empty())
				{
					uint64_t entries = block.MetaData.size();

					for (auto i = 0; i < entries; i++)
						if (block.MetaData[i].Name == resourceName)
						{
							int location = block.Locations[i];
							block.Resources[i].Data = std::vector<byte>(block.Sizes[i]);
							f.seekg(location);
							f.read(reinterpret_cast<char*>(&block.Resources[i].Data[0]), block.Sizes[i]);
							return block.Resources[i];
						}
				}
			}
			else std::cout << "\033[1;31m" << "[ResourceSerializer] BLOCK NOT STREAMED!" << "\033[0m" << std::endl;
		}
		else std::cout << "\033[1;31m" << "[ResourceSerializer] BLOCK NOT LOADED!" << "\033[0m" << std::endl;
		f.close();
	}
	else std::cout << "\033[1;31m" << "COULDN'T FIND RESOURCE: " << resourceName << " ------ " << block.FilePath << "\033[0m" << std::endl;

	return {};
}


std::vector<byte> ResourceSerializer::StreamDirect(const std::string& resourceName, ResourceBlock& block)
{
	std::ifstream f;
	f.open(block.FilePath, std::ios::binary | std::ios::in);

	if (f.is_open())
	{
		if (block.IsLoaded)
		{
			if (block.IsStreamed)
			{
				if (!block.Resources.empty())
				{
					uint64_t entries = block.MetaData.size();
					for (auto i = 0; i < entries; i++)
						if (block.MetaData[i].Name == resourceName)
						{
							int location = block.Locations[i];
							auto result = std::vector<byte>(block.Sizes[i]);
							f.seekg(location);
							f.read(reinterpret_cast<char*>(&result[0]), block.Sizes[i]);
							return result;
						}
				}
			}
			else std::cout << "\033[1;31m" << "[ResourceSerializer] BLOCK NOT STREAMED!" << "\033[0m" << std::endl;
		}
		else std::cout << "\033[1;31m" << "[ResourceSerializer] BLOCK NOT LOADED!" << "\033[0m" << std::endl;
		f.close();
	}
	else std::cout << "COULDN'T FIND RESOURCE: " << resourceName << "\n" << block.FilePath;
	return std::vector<byte>();
}

ResourceData ResourceSerializer::Get(const std::string& resourceName, const ResourceBlock& block)
{

	if (block.IsLoaded)
	{
		if (!block.IsStreamed)
		{
			if (!block.Resources.empty())
			{
				for (auto i = 0; i < block.MetaData.size(); i++)
					if (block.MetaData[i].Name == resourceName)
						return block.Resources[i];
			}

		}
		else std::cout << "\033[1;31m" << "[ResourceSerializer] BLOCK WAS STREAMED!: UNSUPPORTED - USE GetFromStream instead or StreamDirect" << "\033[0m" << std::endl;
	}
	else std::cout << "\033[1;31m" << "[ResourceSerializer] BLOCK NOT LOADED!" << "\033[0m" << std::endl;
	return {};
}

void ResourceSerializer::Add(const std::string& filepath, const std::string& resourceName, ResourceType type, ResourceBlock& block)
{
	std::ifstream f;
	f.open(filepath, std::ios::binary | std::ios::in);

	f.seekg(0, f.end);
	int length = f.tellg();
	f.seekg(0, f.beg);

	if (f.is_open())
	{
		ResourceMetadata md;
		md.Name = resourceName;
		md.Type = type;

		ResourceData rd;
		rd.Data = std::vector<byte>(length);

		f.read(reinterpret_cast<char*>(&rd.Data[0]), length);

		block.Resources.push_back(rd);
		block.MetaData.push_back(md);
	}
	else std::cout << "COULDN'T FIND RESOURCE: " << resourceName << "\n" << block.FilePath;
}

void ResourceSerializer::Delete(const std::string& resourceName, ResourceBlock& block)
{
	if (!block.Resources.empty())
	{
		for (auto i = 0; i < block.Resources.size(); i++)
		{
			if (block.MetaData[i].Name == resourceName)
			{
				block.Resources[i].Data.clear();
				block.MetaData.erase(block.MetaData.begin() + i);
				block.Locations.erase(block.Locations.begin() + i);
				block.Resources.erase(block.Resources.begin() + i);
				block.Sizes.erase(block.Sizes.begin() + i);
			}
		}
	}
}


ResourceBlock& ResourceSerializer::CreateResourceBlock(const std::string& filepath, const DatType type)
{
	auto rb = new ResourceBlock();
	rb->Type = type;
	rb->FilePath = filepath;
	return *rb;
}

void ResourceSerializer::DeleteBlock(ResourceBlock* rb)
{
	rb->MetaData.clear();
	rb->Resources.clear();
	rb->Locations.clear();
	delete rb;
}

static std::vector<char> ReadAllBytes(char const* filename)
{
	std::ifstream ifs(filename, std::ios::binary | std::ios::ate);
	std::ifstream::pos_type pos = ifs.tellg();

	std::vector<char> result(pos);

	ifs.seekg(0, std::ios::beg);
	ifs.read(&result[0], pos);

	return result;
}

ResourceSerializer::~ResourceSerializer()
{
}