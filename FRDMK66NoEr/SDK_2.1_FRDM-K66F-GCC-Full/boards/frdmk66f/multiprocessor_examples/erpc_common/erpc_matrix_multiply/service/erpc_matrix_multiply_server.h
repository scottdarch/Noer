/*
 * Generated by erpcgen 1.3.0 on Mon Sep  5 16:12:47 2016.
 *
 * AUTOGENERATED - DO NOT EDIT
 */

#if !defined(_erpc_matrix_multiply_server_h_)
#define _erpc_matrix_multiply_server_h_


#ifdef __cplusplus
#include "erpc_matrix_multiply.h"
#include "server.h"
#include <stdint.h>
#include <stdbool.h>


/*!
 * @brief Service subclass for MatrixMultiplyService.
 */
class MatrixMultiplyService_service : public erpc::Service
{
public:
    MatrixMultiplyService_service() : Service(kMatrixMultiplyService_service_id) {}

    /*! @brief Call the correct server shim based on method unique ID. */
    virtual erpc_status_t handleInvocation(uint32_t methodId, uint32_t sequence, erpc::Codec * in, erpc::Codec * out);

private:
    /*! @brief Server shim for erpcMatrixMultiply of MatrixMultiplyService interface. */
    erpc_status_t erpcMatrixMultiply_shim(erpc::Codec * in, erpc::Codec * out, uint32_t sequence);
};

extern "C" {
#endif

typedef void * erpc_service_t;

erpc_service_t create_MatrixMultiplyService_service(void);
#ifdef __cplusplus
}
#endif

#endif // _erpc_matrix_multiply_server_h_
