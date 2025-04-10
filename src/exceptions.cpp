#include "exceptions.hpp"
#include <pvxs/client.h>

labview::ErrCode
err2code()
{
    try {
        throw;
    } catch (const labview::lv_err& e) {
        return e.code;
    } catch (const pvxs::NoConvert& e) {
        static_cast<void>(e); // Supress unreferenced variable warning
        return PVALVError::cannot_convert_value;
    } catch (const pvxs::LookupError& e) {
        static_cast<void>(e);
        return PVALVError::field_missing;
    } catch (const pvxs::client::Interrupted& e) {
        static_cast<void>(e);
        return PVALVError::interrupted;
    } catch (const pvxs::client::Timeout& e) {
        static_cast<void>(e);
        return PVALVError::timeout;
    } catch (...) {
        return PVALVError::unspecified;
    }
    return PVALVError::no_err;
}
