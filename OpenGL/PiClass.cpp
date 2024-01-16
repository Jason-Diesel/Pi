#include "PiClass.h"


PiClass::PiClass(const std::string& readFile, ShaderHandler* sh, ResourceManager* rm, const glm::ivec2& windowSize)
{
    createTexture(windowSize);
    this->sh = sh;
    computeShader = rm->getShader("PiCompute.comp");
    PiConstantBufferData.textureWidth = windowSize.x;
    PiConstantBufferData.textureHeight = windowSize.y;
    PiConstantBufferData.currentWidth = windowSize.x;
    PiConstantBufferData.groupsOf = 1;
    PiConstantBufferData.color = 0;
    PiConstantBufferData.offset = 0;
    PiConstantBufferData.zoom = 1;

    UniformBuffer UBPi(PiConstantBufferData, "PiUpdate", 6);
    sh->AddBuffer("PiUpdate", UBPi);

    struct stat buffer;
    if (!stat("../1_BillionPi.dat", &buffer) == 0){
        if (!stat("../pi-billion.txt", &buffer) == 0)
        {
            std::cout << "error cannot find pi" << std::endl;
            exit(-1);
        }
        else {
            readTextFile("../pi-billion.txt");
            writeToBinaryFile("../1_BillionPi.dat");
        }
    }
    else {
        readBinaryFile(readFile.c_str());
    }

    VAO = CreateVertexArray();
    CreateNumberBuffer(data);
}

void PiClass::writeToBinaryFile(const std::string& fileName)
{
    std::ofstream output(fileName, std::ios::binary);
    if (!output.is_open()) {
        return;
    }
    uint32_t size = data.size();
    output.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));
    output.write(reinterpret_cast<const char*>(data.data()), sizeof(uint8_t) * data.size());
    output.close();
}

void PiClass::update()
{
    uint32_t z = 0;
    glClearTexImage(texture, 0, GL_RGBA, GL_UNSIGNED_BYTE, &z);

    this->sh->setCurrentshader(this->computeShader);
    sh->updateUniformBuffer("PiUpdate", PiConstantBufferData);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture);

    glDispatchCompute(16200, 1, 1);//what should be here instead of 60
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

uint32_t PiClass::getTexture()
{
	return this->texture;
}

PiUpdate& PiClass::getPiUpdateData()
{
    return this->PiConstantBufferData;
}

void PiClass::readTextFile(const std::string& readFile)
{
    std::string line;
    FILE* file;
    fopen_s(&file, readFile.c_str(), "r");

    int c;

    if (file == NULL) return; //could not open file
    fseek(file, 0, SEEK_END);
    long f_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    data.reserve(f_size);

    while ((c = fgetc(file)) != EOF) {
        if ((char)c != '.' && (char)c != '\n') {
            data.push_back((uint8_t)(c - '0'));
            if (data.back() < 0 || data.back() > 9) {
                std::cout << "error" << std::endl;//this should never be ran
            }
        }
        else {
            std::cout << "ah" << std::endl;//this should be run once beacuse of the . in 3.14
        }
    }
    std::cout << "done reading file" << std::endl;
    fclose(file);
}

void PiClass::readBinaryFile(const std::string& readFile)
{
    std::ifstream input(readFile, std::ios::binary);
    if (!input.is_open())
    {
        return;
    }

    int size = 0;
    input.read((char*)&size, sizeof(uint32_t));
    data.resize(size);
    input.read((char*)&data[0], sizeof(uint8_t) * size);
    input.close();
}

void PiClass::imguiManager()
{
}

void PiClass::createTexture(const glm::ivec2& windowSize)
{
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//remove blur
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//remove blur

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, windowSize.x, windowSize.y, 0, GL_RGBA, GL_FLOAT, NULL);

    glBindImageTexture(0, texture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
}
