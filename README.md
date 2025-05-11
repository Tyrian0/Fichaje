# Fichaje

**Fichaje** es una aplicación de escritorio desarrollada en C++ y Qt, gestionada con CMake. Proporciona una interfaz gráfica para registrar y gestionar tu control horario de forma sencilla.

## Características

* Interfaz gráfica con Qt Widgets
* Registro de entradas y salidas con un solo clic
* Visualización del tiempo trabajado hoy y esta semana
* Exportación de datos a fichero de texto
* Configuración de sincronización de datos a través de Google Drive

## Requisitos

* **Sistema operativo**: Windows o macOS
* **C++**: Compatibilidad con C++17 o superior
* **Qt**: Versión 5.9 o superior (compatible con Qt6)
* **CMake**: Versión 3.5 o superior
* **Compilador**: MSVC en Windows, Clang en macOS (compatible con C++17)

## Estructura del proyecto

La estructura de carpetas y archivos del proyecto es la siguiente:

```plain
app/
├── CMakeLists.txt           # Configuración principal de CMake
├── resources/               # Contiene el icono de la aplicación
└── src/
    ├── main.cpp             # Punto de entrada de la aplicación
    ├── mainwindow.h         # Declaración de la clase MainWindow
    ├── mainwindow.cpp       # Definición de la clase MainWindow
    └── mainwindow.ui        # Diseño de la interfaz (Qt Designer)
```

## Instalación y compilación

### Windows

1. Clona el repositorio:

   ```bash
   git clone https://github.com/Tyrian0/Fichaje.git
   cd Fichaje
   ```
2. Abre el proyecto `CMakeLists.txt` en Qt Creator:

   * Selecciona la carpeta clonada.
   * Qt Creator detectará automáticamente la configuración de CMake.
3. Compila y ejecuta la aplicación desde Qt Creator.

### macOS

1. Clona el repositorio:

   ```bash
   git clone https://github.com/Tyrian0/Fichaje.git
   cd Fichaje
   ```
2. Da permisos al script:

   ```bash
   chmod +x build.sh  # dar permisos
   ```
3. Usa el script según la acción deseada:

   * `./build.sh` : Configura, compila e instala (en `install/`).
   * `./build.sh build` : Sólo compila (tras haber configurado antes).
   * `./build.sh clean` : Elimina `build/` e `install/`.
   * `./build.sh rebuild` : Limpia todo, vuelve a configurar y compila.

## Uso

1. En la ventana principal, selecciona la fecha y la hora deseadas (se actualizan automáticamente a la fecha y hora actual).
2. Pulsa el botón **Fichar** para registrar una entrada o salida.
3. La etiqueta **Tiempo trabajado hoy** muestra el total acumulado del día (incluye tiempo en curso).
4. La etiqueta **Tiempo trabajado esta semana** muestra el total de lunes a domingo.
5. Para obtener un informe, selecciona el mes y pulsa **Exportar**. Se generará un fichero de texto con los datos del mes seleccionado.

## Ejecutar en varios equipos

Para sincronizar el historial de fichajes entre varios equipos, se recomienda usar Google Drive creando una carpeta compartida `Fichaje`.

### Windows

1. Crea la carpeta `Fichaje` en Google Drive (por ejemplo, en `G:\Mi unidad\Fichaje`).
2. Abre una terminal de comandos como administrador y ejecuta:

   ```cmd
   mklink /D "%APPDATA%\Fichaje" "G:\Mi unidad\Fichaje"
   ```
3. La aplicación almacenará y leerá los datos en el directorio sincronizado.

### macOS

1. Asegúrate de tener Google Drive instalado y sincronizado.
2. Crea la carpeta compartida `Fichaje` en Google Drive (p. ej. `~/Google Drive/Mi unidad/Fichaje`).
3. Crea un enlace simbólico en tu directorio de soporte de la aplicación:

   ```bash
   ln -s ~/Google\ Drive/Mi\ unidad/Fichaje ~/Library/Application\ Support/Fichaje
   ```

La aplicación leerá y guardará los datos en la carpeta sincronizada.\*

## Licencia

Este proyecto está bajo la licencia MIT. Consulta el archivo [LICENSE](LICENSE) para más detalles.
