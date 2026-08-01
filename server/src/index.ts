import express from "express";
import { PrismaClient } from "@prisma/client";
import { PrismaPg } from "@prisma/adapter-pg";
import { Pool } from "pg";

const pool = new Pool({ connectionString: process.env.DATABASE_URL });
const adapter = new PrismaPg(pool);
const prisma = new PrismaClient({ adapter });

const app = express();
app.use(express.json());

app.post('/api/transactions', async (req, res) => {
    try {
        const transaction = await prisma.transaction.create({
            data: {
                name: req.body.name,
                phoneNumber: req.body.phoneNumber,
                vehicleNumber: req.body.vehicleNumber,
                vehicleType: req.body.vehicleType,
                material: req.body.material,
                ratePerKG: req.body.ratePerKG,
                grossWeight: req.body.grossWeight,
                tareWeight: req.body.tareWeight,
                netWeight: req.body.netWeight,
                price: req.body.price,
                dateTime: req.body.dateTime,
                location: req.body.location,
                status: req.body.status
            }
        });
        res.status(201).json({ success: true, data: transaction });
    } catch (error: any) {
        console.error("Error creating transaction:", error);
        res.status(500).json({ success: false, error: error.message });
    }
});

app.listen(3000, () => {
    console.log('Server running on port 3000');
});