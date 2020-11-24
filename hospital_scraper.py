from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.support.ui import Select

import time

import xlsxwriter

# cd C:\Users\Nika\Desktop\JustSomeProgramming\Python\hospital_scraping

# python hospital_scraper.py

# stats

URL = 'https://transparency2.transunioncleariq.com/CHIHealth/Rates.aspx'
hospitals_dropdown_name = 'ctl00$phBody$ddlFacilities'
category_id_prefix = 'phBody_gvGroups_LinkButton1_'
hospital_count = 15
category_count = 12
prices_table_id = 'phBody_gvProcedures'
selected_page_table_index = 5
agree_button_id = 'phBody_btnAgree'

selected_category_class = 'selectedRowStyle'
selected_category_class_index = 1

column_name = 'headerText'

# start the driver stuff

driver_path = r'C:\Users\Nika\Downloads\geckodriver.exe'
driver = webdriver.Firefox(executable_path = driver_path)

ping_seconds = 10

driver.set_page_load_timeout(ping_seconds)
driver.get(URL)

agree_button = driver.find_element_by_id(agree_button_id)
agree_button.click()

time.sleep(ping_seconds)

hospitals_dropdown = driver.find_element_by_name(hospitals_dropdown_name)

hospital_elements = hospitals_dropdown.find_elements_by_tag_name('option')

hospitals = []

data = [] # hospital name and array of categories each with table

for element in hospital_elements:
	hospitals.append(element.text)

hospital_index = 0

wanted_hospitals = 2
wanted_categories = 3

for hospital in hospitals:
	if hospital_index == wanted_hospitals:
		break

	# hospitals_dropdown = driver.find_element_by_name(hospitals_dropdown_name)
	
	print('Checking for ' + hospital)

	# hospitals_dropdown.select_by_visible_text(hospital)

	hospital_index += 1

	driver.find_element_by_xpath('//select/option[' + str(hospital_index) + ']').click()

	time.sleep(ping_seconds)

	categories_data = []

	hospital_data = [hospital]

	for i in range(category_count):
		if i == wanted_categories:
			break

		category_id = category_id_prefix + str(i)

		category = driver.find_element_by_id(category_id)

		rows = []
		category_data = [category.text]

		print('Starting for category ' + category.text)

		category.click()

		time.sleep(ping_seconds)

		# prices_table = driver.find_element_by_id(prices_table_id)

		column_elements = driver.find_elements_by_class_name(column_name)
		columns = []

		for column_element in column_elements:
			columns.append(column_element.text)

		rows.append(columns)

		all_rows = driver.find_elements_by_xpath('//table/tbody/tr')

		data_rows = all_rows[1:-1]
		page_row = all_rows[-1] # TODO crawl through pages

		for data_row in data_rows:
			fields = []

			for field in data_row.find_elements_by_tag_name('td'):
				fields.append(field.text)

			rows.append(fields)

		category_data.append(columns) # each category might have different columns for all we know
		category_data.append(rows)
		categories_data.append(category_data)

		print('Done for category ' + category_id)

	hospital_data.append(categories_data)
	data.append(hospital_data)

	print('Done for ' + hospital)

driver.quit()

print('Driver out')

# we have data, now write it to excel

print('Data we have:')
print(data)

workbook = xlsxwriter.Workbook('result.xlsx')

for datum in data:
	hospital = datum[0]
	categories_data = datum[1]

	sheet_name = hospital if len(hospital) <= 31 else hospital[:31]
	sheet = workbook.add_worksheet(sheet_name)

	sheet.write(0, 0, hospital)

	y = 1

	for category_data in categories_data:
		category_name = category_data[0]
		columns = category_data[1]
		rows = category_data[2]

		y += 1

		sheet.write(y, 0, category_name)
		
		y += 1
		x = 0

		for column in columns:
			sheet.write(y, x, column)
			x += 1	

		for row in rows:
			x = 0
			y += 1

			for field in row:
				sheet.write(y, x, field)
				x += 1

workbook.close()