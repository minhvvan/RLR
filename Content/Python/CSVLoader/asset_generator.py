import unreal
import os
import csv
import sys


# 프로젝트 명
project_name = "RLR"

# 데이터 테이블 클래스
asset_class = unreal.DataTable

# 데이터 테이블 에셋 저장 경로
asset_path = "/Game/DataTable"

# CSV 파일이 존재하는 폴더 경로
csv_folder = unreal.SystemLibrary.get_project_directory() + "Data"


# struct_path : ex) "/Script/RottenPotato.TestTable"
# 데이터 테이블 에셋 생성 함수
def create_data_table_asset(csv_path):
    # 파일명
    file_name = str(os.path.basename(csv_path)).split('.')[0]
    # 데이터 테이블 파일명
    asset_name = "DT_" + file_name
    # base struct 스크립트 경로
    if "ClassData" in file_name:
        file_name = "ClassData"
    elif "TextStyle" in file_name:
        file_name = "RichTextStyleRow"

    unreal_struct_path = "/Script/" + project_name + "." + file_name

    print("--------- Creating data table asset..." + " Struct path : " + unreal_struct_path + " ----------")
    print("-")
    # 데이터 테이블 구조체
    asset_factory = unreal.DataTableFactory()
    asset_factory.struct = unreal.load_object(None, unreal_struct_path)
    if asset_factory.struct is None:
        unreal.log_error("Asset factory struct is none.")
        return

    csv_factory = unreal.CSVImportFactory()
    csv_factory.automated_import_settings.import_row_struct = asset_factory.struct

    task = unreal.AssetImportTask()
    task.filename = csv_path
    task.destination_name = asset_name
    task.destination_path = asset_path
    task.replace_existing = True
    task.automated = True
    task.save = True
    task.factory = csv_factory

    unreal.AssetToolsHelpers.get_asset_tools().import_asset_tasks([task])

# 시작 함수
def start():
    print("#######   Data Table Asset Generator Started!     #######")
    print("######    Target CSV Folder : " + csv_folder)
    print("-")
    # csv_folder 내부의 모든 파일 리스트 검출
    file_list = os.listdir(csv_folder)

    csv_file_list = []
    # CSV 가 아닌 것 걸러내기
    for file in file_list:
        if file.endswith(".csv"):
            csv_file_list.append(file)

    if len(csv_file_list) == 0:
        unreal.log_error("There's no CSV file in folder : " + csv_folder)
        sys.exit(0)

    print("----------- CSV File List ------------")
    print("-")
    # 반복문 시작 : 하나 씩 변환 시작
    index = 1
    for file in csv_file_list:
        print("(" + str(index) + ") " + file)
        index += 1

    print("-")
    for file in csv_file_list:
        print("-")
        print("::::::::::::: Start making [" + file + "] ::::::::::::::")
        # csv 파일 경로 추출
        csv_file_path = os.path.join(csv_folder, file)
        create_data_table_asset(csv_file_path)


# 실행 부분
start()
print("********* Asset Generator Closed. **********")