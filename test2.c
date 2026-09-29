#include <stdio.h>

int main(void)
{
    // 商品库存：只在程序开始时初始化
    int stock1 = 10;
    int stock2 = 8;
    int stock3 = 12;

    // 商品单价
    int price1 = 12;
    int price2 = 15;
    int price3 = 10;

    // 当前订单中每种商品的数量
    int qty1 = 0;
    int qty2 = 0;
    int qty3 = 0;

    // 营业统计
    int orderCount = 0;
    int soldCount = 0;
    double revenue = 0;

    // 用户操作
    int running = 1;
    int choice;
    int type;
    int amount;
    int member;
    int confirm;

    // 结账使用的变量
    int total;
    int cups;
    int discount;
    double payable;
    double payment;

    while (running == 1)
    {
        printf("\n======= 奶茶店收银系统 =======\n");
        printf("1. 查看商品和库存\n");
        printf("2. 添加商品到当前订单\n");
        printf("3. 查看当前订单\n");
        printf("4. 结账\n");
        printf("5. 取消当前订单\n");
        printf("6. 查看营业统计\n");
        printf("0. 退出系统\n");
        printf("请选择：");
        scanf("%d", &choice);

        // 1. 查看商品和库存
        if (choice == 1)
        {
            printf("\n编号  商品        单价    剩余库存\n");
            printf("1     原味奶茶    %d元    %d杯\n",
                   price1, stock1);
            printf("2     珍珠奶茶    %d元    %d杯\n",
                   price2, stock2);
            printf("3     柠檬茶      %d元    %d杯\n",
                   price3, stock3);
        }

        // 2. 添加商品
        else if (choice == 2)
        {
            printf("\n1. 原味奶茶\n");
            printf("2. 珍珠奶茶\n");
            printf("3. 柠檬茶\n");
            printf("请输入商品编号：");
            scanf("%d", &type);

            if (type < 1 || type > 3)
            {
                printf("商品编号无效。\n");
            }
            else
            {
                printf("请输入购买数量：");
                scanf("%d", &amount);

                if (amount <= 0)
                {
                    printf("数量必须大于0。\n");
                }
                else if (type == 1)
                {
                    if (amount > stock1)
                    {
                        printf("库存不足，目前剩余%d杯。\n", stock1);
                    }
                    else
                    {
                        qty1 += amount;
                        stock1 -= amount;
                        printf("已添加%d杯原味奶茶。\n", amount);
                    }
                }
                else if (type == 2)
                {
                    if (amount > stock2)
                    {
                        printf("库存不足，目前剩余%d杯。\n", stock2);
                    }
                    else
                    {
                        qty2 += amount;
                        stock2 -= amount;
                        printf("已添加%d杯珍珠奶茶。\n", amount);
                    }
                }
                else
                {
                    if (amount > stock3)
                    {
                        printf("库存不足，目前剩余%d杯。\n", stock3);
                    }
                    else
                    {
                        qty3 += amount;
                        stock3 -= amount;
                        printf("已添加%d杯柠檬茶。\n", amount);
                    }
                }
            }
        }

        // 3. 查看当前订单
        else if (choice == 3)
        {
            cups = qty1 + qty2 + qty3;

            if (cups == 0)
            {
                printf("当前订单为空。\n");
            }
            else
            {
                printf("\n======= 当前订单 =======\n");

                if (qty1 > 0)
                {
                    printf("原味奶茶：%d杯，小计%d元\n",
                           qty1, qty1 * price1);
                }

                if (qty2 > 0)
                {
                    printf("珍珠奶茶：%d杯，小计%d元\n",
                           qty2, qty2 * price2);
                }

                if (qty3 > 0)
                {
                    printf("柠檬茶：%d杯，小计%d元\n",
                           qty3, qty3 * price3);
                }

                total = qty1 * price1
                      + qty2 * price2
                      + qty3 * price3;

                printf("总杯数：%d杯\n", cups);
                printf("原价总额：%d元\n", total);
            }
        }

        // 4. 结账
        else if (choice == 4)
        {
            cups = qty1 + qty2 + qty3;

            if (cups == 0)
            {
                printf("当前订单为空，不能结账。\n");
            }
            else
            {
                total = qty1 * price1
                      + qty2 * price2
                      + qty3 * price3;

                // 每次结账都重新计算优惠
                discount = 0;

                if (total >= 100)
                {
                    discount = 15;
                }
                else if (total >= 60)
                {
                    discount = 8;
                }

                printf("是否为会员？1是，0否：");
                scanf("%d", &member);

                while (member != 0 && member != 1)
                {
                    printf("输入无效，请输入1或0：");
                    scanf("%d", &member);
                }

                // 先满减，再计算会员折扣
                payable = total - discount;

                if (member == 1)
                {
                    payable *= 0.9;
                }

                printf("\n原价总额：%d元\n", total);
                printf("满减金额：%d元\n", discount);

                if (member == 1)
                {
                    printf("会员优惠：满减后九折\n");
                }

                printf("最终应付：%.2f元\n", payable);
                printf("请输入付款金额：");
                scanf("%lf", &payment);

                while (payment < payable)
                {
                    printf("金额不足，请重新输入付款总额：");
                    scanf("%lf", &payment);
                }

                printf("找零：%.2f元\n", payment - payable);
                printf("结账成功！\n");

                // 只有结账成功才更新营业统计
                orderCount++;
                soldCount += cups;
                revenue += payable;

                // 清空订单，库存已经在添加商品时扣除
                qty1 = 0;
                qty2 = 0;
                qty3 = 0;
            }
        }

        // 5. 取消当前订单
        else if (choice == 5)
        {
            cups = qty1 + qty2 + qty3;

            if (cups == 0)
            {
                printf("没有需要取消的订单。\n");
            }
            else
            {
                // 把当前订单的商品还回库存
                stock1 += qty1;
                stock2 += qty2;
                stock3 += qty3;

                qty1 = 0;
                qty2 = 0;
                qty3 = 0;

                printf("订单已取消，库存已恢复。\n");
            }
        }

        // 6. 查看营业统计
        else if (choice == 6)
        {
            printf("\n======= 营业统计 =======\n");
            printf("已完成订单：%d单\n", orderCount);
            printf("累计售出：%d杯\n", soldCount);
            printf("累计营业额：%.2f元\n", revenue);
        }

        // 0. 退出系统
        else if (choice == 0)
        {
            cups = qty1 + qty2 + qty3;

            if (cups > 0)
            {
                printf("当前还有未结账订单。\n");
                printf("取消订单并退出？1是，0返回菜单：");
                scanf("%d", &confirm);

                while (confirm != 0 && confirm != 1)
                {
                    printf("输入无效，请输入1或0：");
                    scanf("%d", &confirm);
                }

                if (confirm == 1)
                {
                    stock1 += qty1;
                    stock2 += qty2;
                    stock3 += qty3;

                    qty1 = 0;
                    qty2 = 0;
                    qty3 = 0;

                    running = 0;
                }
            }
            else
            {
                running = 0;
            }
        }

        // 其他选项
        else
        {
            printf("无效选项，请重新选择。\n");
        }
    }

    printf("\n======= 最终营业统计 =======\n");
    printf("已完成订单：%d单\n", orderCount);
    printf("累计售出：%d杯\n", soldCount);
    printf("累计营业额：%.2f元\n", revenue);
    printf("系统已退出。\n");

    return 0;
}