//
// Created by bios on 9/11/23.
//

#include "OpenGLTexture.h"
#include "../../../vendor/stb/stb_image.h"
#include "../../Core/Log.h"
namespace VectorVertex{
OpenGLTexture::OpenGLTexture(VectorVertex::TextureData data):m_Data(data) {
  int width_img, height_img, num_color_ch;
  stbi_set_flip_vertically_on_load(true);
  unsigned char* bytes = stbi_load(m_Data.image.c_str(), &width_img, &height_img, &num_color_ch, 0);
  glGenTextures(1, &m_Data.ID);
  glActiveTexture(GL_TEXTURE0+m_Data.unit);
  glBindTexture(GL_TEXTURE_2D, m_Data.ID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  //gl s t r = x y z
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  if(num_color_ch == 4){
    glTexImage2D
        (
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            width_img,
            height_img,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            bytes
        );
  } else if(num_color_ch == 3){
    glTexImage2D
        (
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            width_img,
            height_img,
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            bytes
        );
  } else if(num_color_ch == 1){
    glTexImage2D
        (
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            width_img,
            height_img,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            bytes
        );
  } else{
    throw std::invalid_argument("Automatic Texture type recognition failed!");
  }

  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(bytes);
  glBindTexture(GL_TEXTURE_2D, 0);
}
void OpenGLTexture::texUni(Ref<VectorVertex::Shader> _shader, std::string uniform, unsigned int unit) {
  _shader->Activate();
  _shader->SetInt(uniform, unit);
}
void OpenGLTexture::Bind() {
  glActiveTexture(GL_TEXTURE0+m_Data.unit);
  glBindTexture(GL_TEXTURE_2D, m_Data.ID);
}
void OpenGLTexture::Unbind() {
  glBindTexture(GL_TEXTURE_2D, 0);
}
void OpenGLTexture::Delete() {
  VV_CORE_WARN("GLTexture Deleted!");
  glDeleteTextures(1, &m_Data.ID);
}
}