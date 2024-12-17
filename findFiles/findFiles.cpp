#include <filesystem>
#include <iostream>
namespace fs = std::filesystem;
using namespace std;

void SortFiles(const fs::path& folder)
{
	fs::path parent_dir = folder.parent_path();
	fs::path images_dir = parent_dir;
	fs::path labels_dir = parent_dir;
	images_dir /= "images";
	labels_dir /= "labels";
	// создаём папки новые
	fs::create_directory(images_dir);
	fs::create_directory(labels_dir);

	// сортировка
	for (auto& file : fs::directory_iterator(folder))
	{
		fs::path curr_file = file.path();	// получаем текущий объект
		if (fs::exists(curr_file) && fs::is_regular_file(curr_file))	// проверяем существует ли он
		{
			bool res = false;
			if (curr_file.extension() == ".jpg")
			{
				// копируем в папку images
				fs::path target_file = images_dir;
				target_file /= curr_file.filename();
				res = fs::copy_file(curr_file, target_file, fs::copy_options::overwrite_existing);
			}
			else if (curr_file.extension() == ".txt")
			{
				// копируем в папку labels
				fs::path target_file = labels_dir;
				target_file /= curr_file.filename();
				res = fs::copy_file(curr_file, target_file, fs::copy_options::overwrite_existing);
			}
			if (res)
			{
				setlocale(LC_ALL, "ru-RU");
				cout << "Файл " << curr_file.filename() << " скопирован.\n";
				res = fs::remove(curr_file);
				if (res) cout << "Файл " << curr_file.filename() << " удалён.\n";
			}
		}
	}
}

int main()
{
	fs::path curr_dir = fs::current_path();
	curr_dir /= "files";
	SortFiles(curr_dir);
}