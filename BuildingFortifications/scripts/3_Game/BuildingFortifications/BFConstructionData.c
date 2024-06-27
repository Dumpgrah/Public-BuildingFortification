//! Data structure classes for BF configuration file used to set and modify the needed quantity for certain materials to build
//! a part on a building fortifications object.
class BFConstructionData
{
    string ClassName;
    string PartName;
    ref array<ref BFConstructionMaterial> Materials = new array<ref BFConstructionMaterial>;

    void BFConstructionData(string className, string partName)
    {
        ClassName = className;
        PartName = partName;
    }

    void AddMaterial(string slotName, int quantity)
    {
        BFConstructionMaterial mat = new BFConstructionMaterial(slotName, quantity);
        Materials.Insert(mat);
    }

    array<ref BFConstructionMaterial> GetMaterials()
    {
        return Materials;
    }

    BFConstructionMaterial GetMaterialDataByForSlot(string slotName)
    {
        BFConstructionMaterial foundMat;
        foreach (BFConstructionMaterial currentMat: Materials)
        {
            if (currentMat.SlotName == slotName)
                foundMat = currentMat;
        }

        return foundMat;
    }

    bool GetMaterialQuantityForSlot(string slotName, out int quantity)
    {
		//PrintFormat("%1::GetMaterialQuantityForSlot - Slot name=%2", ToString(), slotName);
        bool found;
        foreach (BFConstructionMaterial currentMat: Materials)
        {
            if (currentMat.SlotName == slotName)
            {
                quantity = currentMat.Quantity;
                found = true;
				//PrintFormat("%1::GetMaterialQuantityForSlot - Found quantity! Slot name=%2 | Quantity=%3", ToString(), slotName, quantity);
            }
        }

        return found;
    }

#ifdef DIAG
    void Debug()
    {
        Print("----------------------------------------");
        Print(ToString() + "::Debug - ClassName: " + ClassName);
        Print(ToString() + "::Debug - PartName: " + PartName);
        foreach (BFConstructionMaterial data: Materials)
		{
			data.Debug();
		}
        Print("----------------------------------------");
    }
#endif

	void OnSend(ParamsWriteContext ctx)
	{
		ctx.Write(ClassName);
		ctx.Write(PartName);
		ctx.Write(Materials.Count());
		
		for (int i = 0; i < Materials.Count(); i++)
		{
			Materials[i].OnSend(ctx);
		}		
	}

	bool OnRecive(ParamsReadContext ctx)
	{
		if (!ctx.Read(ClassName))
			return false;
		
		if (!ctx.Read(PartName))
			return false;
		
		int constMatCount;
		if (!ctx.Read(constMatCount))
			return false;
		
		for (int i = 0; i < constMatCount; i++)
		{
			BFConstructionMaterial mat = new BFConstructionMaterial("", 0);
			if (!mat.OnRecive(ctx))
				return false;

			Materials.Insert(mat);
		}
		
		return true;
	}
};

class BFConstructionMaterial
{
    string SlotName;
    int Quantity;

    void BFConstructionMaterial(string slotName, int quantity)
    {
        SlotName = slotName;
        Quantity = quantity;
    }

	void OnSend(ParamsWriteContext ctx)
	{
		ctx.Write(SlotName);
		ctx.Write(Quantity);
	}

	bool OnRecive(ParamsReadContext ctx)
	{
		if (!ctx.Read(SlotName))
			return false;
		
		if (!ctx.Read(Quantity))
			return false;
		
		return true;
	}

#ifdef DIAG
    void Debug()
    {
        Print("----------------------------------------");
        Print(ToString() + "::Debug - SlotName: " + SlotName);
        Print(ToString() + "::Debug - Quantity: " + Quantity);
        Print("----------------------------------------");
    }
#endif
};