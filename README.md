# Programming_Control_System_ITMO

# Ход работы

Справедливо для файла filename = 'process_log_13_03_2023_11_19_37.csv';

![изображение](https://user-images.githubusercontent.com/42892348/226342851-df066639-c5dd-418a-b645-8c8ce1d8695c.png)

Фильтрация по умолчанию

![изображение](https://user-images.githubusercontent.com/42892348/226343033-86c442be-bfd0-4a44-9b87-ead9ed01ede1.png)


Результат приближения при параметрах:

b = 0.9827;
a1 = 2.9780;
a0 = 0.5452;

![изображение](https://user-images.githubusercontent.com/42892348/226343141-cfcec5f4-25f7-4eb6-8d9c-3d85c299ed81.png)

Фильтрация при использовании lowpass

![изображение](https://user-images.githubusercontent.com/42892348/226343418-b3368779-e63c-4c1f-8032-db25c6771561.png)


**Для более сложной гармоники имеем следующее:**

![изображение](https://user-images.githubusercontent.com/42892348/226349097-2e4715b8-cd38-452a-8f6e-56d2bd37c2fd.png)

![изображение](https://user-images.githubusercontent.com/42892348/226349213-80d58afb-ed20-46b3-94b9-66ac07f11769.png)

![изображение](https://user-images.githubusercontent.com/42892348/226349355-1ad4811e-80c3-41df-8815-6e3db2ca00b0.png)

![изображение](https://user-images.githubusercontent.com/42892348/226349435-d4069341-53c6-4ff9-933d-f8b84dfab434.png)

Моделирование для параметров:

b = 0.9827; b = 1.028;
a1 = 2.9780; a1 = 3.1619;
a0 = 0.5452; a0 = 0.5905;

Для первой тройки:

![изображение](https://user-images.githubusercontent.com/42892348/226349850-b1ef1779-e163-44c9-bcec-df089ed4aa65.png)


Для последней тройки:

![изображение](https://user-images.githubusercontent.com/42892348/226349697-185b2a0a-7506-4ae3-9972-d339d5192cc8.png)


# Настройка Пид регулятора

Вот неплохие параметры, но попробую лучше

![изображение](https://user-images.githubusercontent.com/42892348/226409939-dd6d6c78-8f7c-46cc-b1f1-a80c12ceb697.png)

Вот более подходящие параметры

![изображение](https://user-images.githubusercontent.com/42892348/226413359-51842185-08b8-4786-8aab-578191731f8f.png)

Вот график передаточной

![изображение](https://user-images.githubusercontent.com/42892348/226413651-4db4aac3-a36d-4fab-9ddd-8b9633d45f05.png)

Входит в 5% окно

![изображение](https://user-images.githubusercontent.com/42892348/226413753-9f7ed0ed-04ea-40a3-82f5-0f0872a20f06.png)

График ошибки

![изображение](https://user-images.githubusercontent.com/42892348/226414246-e6f003ae-73d6-4a12-b16c-8f5d3fa971eb.png)


Схема модели:

![изображение](https://user-images.githubusercontent.com/42892348/226414416-b2a1c527-6d83-4b6c-8c4a-f0f7e75c9a02.png)



Типо слежение, если подавать Y на вход, не управление, а что хотим 

![изображение](https://user-images.githubusercontent.com/42892348/226415921-df74be8e-8439-47d6-a3fc-db671b1e8e68.png)


# Передаточная ПИД регулятора и форма в пространстве состояния

![изображение](https://user-images.githubusercontent.com/42892348/226425269-e8c27a05-6dd2-4ed7-ba6d-e2884af37adc.png)

![изображение](https://user-images.githubusercontent.com/42892348/226425376-2753bb61-e774-4366-b8aa-29710000d5e5.png)

Подставим в модель Симулинк

![изображение](https://user-images.githubusercontent.com/42892348/226425514-981a8f26-71c7-46e0-bdf7-3291144dd87e.png)

![изображение](https://user-images.githubusercontent.com/42892348/226425579-b1cfa312-b8c9-402a-882d-acd59fd5a800.png)

![изображение](https://user-images.githubusercontent.com/42892348/226425709-e331f220-de0b-4176-a426-e4f0a5aa429d.png)

Можно каноническую получить

![изображение](https://user-images.githubusercontent.com/42892348/226427084-58295f57-1c99-4f16-b40e-1e7850c9de9c.png)


Для непрерывного ПИД

![image](https://user-images.githubusercontent.com/42892348/227721454-a16609fc-c517-465c-a4ab-355285b7780a.png)



https://www.youtube.com/watch?v=9Z0pkDSp4I8

https://www.mathworks.com/matlabcentral/answers/513723-convert-a-transfer-function-to-controllable-and-observable-canonical-form
