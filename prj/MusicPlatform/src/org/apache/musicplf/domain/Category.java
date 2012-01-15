package org.apache.musicplf.domain;

public class Category 
{
    private Integer id;
    private String name;
    private String superiorCategory;
    private String remark;
    
    public Integer getId()
    {
        return id;
    }
    
    public void setId(Integer id)
    {
        this.id = id;
    }

    public String getName() 
    {
        return name;
    }

    public void setName(String name) 
    {
        this.name = name;
    }

    public String getSuperiorCategory() 
    {
        return superiorCategory;
    }

    public void setSuperiorCategory(String superiorCategory) 
    {
        this.superiorCategory = superiorCategory;
    }

    public String getRemark()
    {
        return remark;
    }

    public void setRemark(String remark)
    {
        this.remark = remark;
    }
}