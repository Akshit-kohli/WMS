-- CreateEnum
CREATE TYPE "TransactionStatus" AS ENUM ('CREATED', 'GROSS_CAPTURED', 'COMPLETED', 'UNKNOWN');

-- CreateTable
CREATE TABLE "Transaction" (
    "id" UUID NOT NULL,
    "name" TEXT NOT NULL,
    "phoneNumber" TEXT NOT NULL,
    "vehicleNumber" TEXT NOT NULL,
    "vehicleType" TEXT NOT NULL,
    "material" TEXT NOT NULL,
    "ratePerKG" DOUBLE PRECISION NOT NULL,
    "grossWeight" DOUBLE PRECISION NOT NULL,
    "tareWeight" DOUBLE PRECISION NOT NULL,
    "netWeight" DOUBLE PRECISION NOT NULL,
    "charge" DOUBLE PRECISION NOT NULL,
    "dateTime" TEXT NOT NULL,
    "location" TEXT NOT NULL,
    "status" "TransactionStatus" NOT NULL DEFAULT 'CREATED',
    "createdAt" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "updatedAt" TIMESTAMP(3) NOT NULL,

    CONSTRAINT "Transaction_pkey" PRIMARY KEY ("id")
);

-- CreateIndex
CREATE INDEX "Transaction_vehicleNumber_idx" ON "Transaction"("vehicleNumber");

-- CreateIndex
CREATE INDEX "Transaction_status_idx" ON "Transaction"("status");
