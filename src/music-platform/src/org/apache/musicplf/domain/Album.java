package org.apache.musicplf.domain;

public class Album 
{
    private Integer id;
    private String abmName;
    private Integer recordcompanyId;

    public Integer getId() 
    {
        return id;
    }

    public void setId(Integer id)
    {
        this.id = id;
    }

    public String getAbmName()
    {
        return abmName;
    }

    public void setAbmName(String abmName)
    {
        this.abmName = abmName;
    }

    public Integer getRecordcompanyId() 
    {
        return recordcompanyId;
    }
    
    public void setRecordcompanyId(Integer recordcompanyId) 
    {
        this.recordcompanyId = recordcompanyId;
    }
}