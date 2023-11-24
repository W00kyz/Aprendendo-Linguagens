import os
import re

def create_folder_structure(root_folder):
    def parse_readme(file_path):
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()
        sections = re.split(r'\n##\s+', content)[1:]  # Split content by ## (header 2)
        return sections

    def create_subfolders(parent_folder, items):
        for item in items:
            lines = item.split('\n')
            subfolder_name = lines[0].strip()
            subfolder_name_underlined = subfolder_name.replace(" ", "_")
            subfolder_path = os.path.join(parent_folder, subfolder_name_underlined)
            os.makedirs(subfolder_path, exist_ok=True)
            
            nested_lists = re.findall(r'\n(\s*)[*-]\s+(.+)', item)
            if nested_lists:
                create_subfolders(subfolder_path, [f"{indent}{content}" for indent, content in nested_lists])

            # Create README.md with Table of Contents
            create_readme(subfolder_path, subfolder_name, nested_lists)

    def create_readme(folder, folder_name, nested_lists):
        readme_path = os.path.join(folder, 'README.md')
        with open(readme_path, 'w', encoding='utf-8') as readme_file:
            folder_name_underlined = folder_name.replace(" ", "_")
            readme_file.write(f"# {folder_name}\n\n")
            if nested_lists:
                readme_file.write("## Table_of_Contents\n")
                for indent, content in nested_lists:
                    level = len(indent) // 2 + 2
                    content_underlined = content.replace(" ", "_")
                    readme_file.write(f"{'  ' * (level - 2)}- [{content}](./{content_underlined}/README.md)\n")
                readme_file.write("\n")

    os.makedirs(root_folder, exist_ok=True)
    readme_path = "./README.md"
    
    if os.path.isfile(readme_path):
        sections = parse_readme(readme_path)
        create_subfolders(root_folder, sections)

        # Create Table of Contents for Root Folder
        with open(os.path.join(root_folder, 'README.md'), 'w', encoding='utf-8') as root_readme_file:
            root_readme_file.write(f"# {root_folder}\n\n## Table_of_Contents\n")
            for section in sections:
                lines = section.split('\n')
                folder_name = lines[0].strip()
                folder_name_underlined = folder_name.replace(" ", "_")
                root_readme_file.write(f"- [{folder_name}](./{folder_name_underlined}/README.md)\n")
            root_readme_file.write("\n")

        # Add link to the root README
        with open(readme_path, 'a', encoding='utf-8') as main_readme_file:
            main_readme_file.write(f"- {root_folder}[{root_folder}](./{root_folder}/README.md)\n")

# Example Usage:
root_directory_name = input("Digite o nome da linguagem: ")
create_folder_structure(root_directory_name)
