//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# define CATCH_CONFIG_FAST_COMPILE
# define CATCH_CONFIG_ENABLE_BENCHMARKING
# include <ThirdParty/Catch2/catch.hpp>

# include <Siv3D.hpp>
using namespace s3d;
using namespace std::literals;

TEST_CASE("FileSystem")
{
	Console << U"FileSystem:";
	Console << (U"Volume\t: {}"_fmt(FileSystem::VolumePath(U"./")));
	Console << (U"Initial\t: {}"_fmt(FileSystem::InitialDirectory()));
	Console << (U"Module\t: {}"_fmt(FileSystem::ModulePath()));
	Console << (U"Current\t: {}"_fmt(FileSystem::CurrentDirectory()));
	Console << (U"Full  \t: {}"_fmt(FileSystem::FullPath(U"./")));
	{
		const auto path = FileSystem::NativePath(U"./");
	# if SIV3D_PLATFORM(WINDOWS)
		Console << (U"Native\t: {}"_fmt(Unicode::FromWstring(path)));
	# else
		Console << (U"Native\t: {}"_fmt(Unicode::Widen(path)));
	# endif
	}
	Console << (U"Parent\t: {}"_fmt(FileSystem::ParentPath(U"./")));
	Console << (U"Parent\t: {}"_fmt(FileSystem::ParentPath(U"./", 1)));
	Console << (U"Parent\t: {}"_fmt(FileSystem::ParentPath(U"./", 2)));

	const FilePath modulePath = FileSystem::ModulePath();
	REQUIRE(FileSystem::Exists(modulePath) == true);
	
# if SIV3D_PLATFORM(MACOS)
	REQUIRE(FileSystem::IsFile(modulePath) == false);
	REQUIRE(FileSystem::IsDirectory(modulePath) == true);
# else
	REQUIRE(FileSystem::IsFile(modulePath) == true);
	REQUIRE(FileSystem::IsDirectory(modulePath) == false);
# endif
	
	REQUIRE(FileSystem::IsResource(modulePath) == false);

	Console << (U"Size\t: {}"_fmt(FileSystem::Size(modulePath)));
	Console << (U"F Size\t: {}"_fmt(FileSystem::FileSize(modulePath)));
	Console << (U"Size\t: {}"_fmt(FileSystem::Size(U"./")));
	Console << (U"Creatio\t: {}"_fmt(FileSystem::CreationTime(modulePath)));
	Console << (U"Write\t: {}"_fmt(FileSystem::WriteTime(modulePath)));
	Console << (U"Access\t: {}"_fmt(FileSystem::AccessTime(modulePath)));
	Console << (U"DirCon\t: {}"_fmt(FileSystem::DirectoryContents(U"./")));


	Console << (U"Desktop\t: {}"_fmt(FileSystem::GetFolderPath(SpecialFolder::Desktop)));
	Console << (U"Documents\t: {}"_fmt(FileSystem::GetFolderPath(SpecialFolder::Documents)));
	Console << (U"LocalAppData\t: {}"_fmt(FileSystem::GetFolderPath(SpecialFolder::LocalAppData)));
	Console << (U"Pictures\t: {}"_fmt(FileSystem::GetFolderPath(SpecialFolder::Pictures)));
	Console << (U"Music\t: {}"_fmt(FileSystem::GetFolderPath(SpecialFolder::Music)));
	Console << (U"Videos\t: {}"_fmt(FileSystem::GetFolderPath(SpecialFolder::Videos)));
	Console << (U"Caches\t: {}"_fmt(FileSystem::GetFolderPath(SpecialFolder::Caches)));
	Console << (U"Movies\t: {}"_fmt(FileSystem::GetFolderPath(SpecialFolder::Movies)));
	Console << (U"SystemFonts\t: {}"_fmt(FileSystem::GetFolderPath(SpecialFolder::SystemFonts)));
	Console << (U"LocalFonts\t: {}"_fmt(FileSystem::GetFolderPath(SpecialFolder::LocalFonts)));
	Console << (U"UserFonts\t: {}"_fmt(FileSystem::GetFolderPath(SpecialFolder::UserFonts)));
	Console << (U"UserProfile\t: {}"_fmt(FileSystem::GetFolderPath(SpecialFolder::UserProfile)));
	Console << (U"ProgramFiles\t: {}"_fmt(FileSystem::GetFolderPath(SpecialFolder::ProgramFiles)));
}
