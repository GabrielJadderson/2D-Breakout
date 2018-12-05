#pragma once
#include "pch.h"




enum DatType : char //the different types of (binary files/.dat files) supported, each with different signature
{
	Resource = 1,
	Library = 2,
};

enum ResourceType : char //the different type of resources contained in a binary file.
{
	None = 0,
	LevelData = 1,
	Scene = 2,
	Save = 3,
	Texture = 4,
	Font = 5,
	Config = 6
};


struct ResourceMetadata
{
	std::string Name;
	ResourceType Type = ResourceType::None;
	//int Location; //location on file
};

// here is the actual resource and it's data
struct ResourceData
{
	std::vector<byte> Data; //our binary data of the resource
};

//this is a collection of resources.
struct ResourceBlock //resource block contains many resources/resource_wrappers
{
	bool IsLoaded = false;
	bool IsStreamed = false;
	std::string FilePath; //path of file on disk.
	DatType Type; //what type? is it a resource or a library or?...
	std::vector<ResourceMetadata> MetaData; //just a list of resources. Each resource must be mapped to a location.
	std::vector<ResourceData> Resources; //just a list of resources. Each resource must be mapped to a location.
	std::vector<int> Locations; //contains a list of locations, first element corresponds to the first location that resources x is stored. eg. if we store a sprite and a text file the first element will contain the location on file the sprite can be indexed. and the second element in this list contains the first location of the text file. etc..
	std::vector<uint64_t> Sizes; //contains the size of data each resource has object spans.



};
