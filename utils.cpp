#include "utils.h"
#include <bcrypt.h>

std::string hash_password(const std::string& password) {
    return bcrypt::generateHash(password);
}
