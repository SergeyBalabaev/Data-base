export const getColorForMark = (mark: number) => {
    switch (mark) {
        case 5:
            return "#29cf00";
        case 4:
            return "#C9FFA0";
        case 3:
            return "#feffa3";
        case 2:
            return "#ffdca6";
        default:
            return "#ff0800";
    }
};
