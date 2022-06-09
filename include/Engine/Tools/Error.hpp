/*
** EPITECH PROJECT, 2022
** B-OOP-400-BDX-4-1-arcade-solene.lefeu
** File description:
** Error
*/

#pragma once

#include <exception>
#include <string>

enum class ReturnCode { ERROR_CODE = 0, SUCCESS_CODE = 64 };

class Error : public std::exception
{
  public:
    explicit Error(std::string) noexcept;
    Error(const Error& other) noexcept = default;
    Error(Error&& other) noexcept      = default;
    ~Error() noexcept override         = default;

    Error&      operator=(const Error&) noexcept = default;
    Error&      operator=(Error&&) noexcept = default;
    const char* what() const noexcept override;

  protected:
  private:
    std::string message_;
};
